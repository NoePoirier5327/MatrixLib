use mlua::prelude::*;
use pokin_core::Matrix;

/// Point d'entré vers le module lua.
#[mlua::lua_module]
fn pokin(lua: &Lua) -> LuaResult<LuaTable> {
    // Tables lua pour l'export de la librairie.
    let exports = lua.create_table()?;
    let matrix_methods = lua.create_table()?;

    // On ajoute les fonctions de construction de matrices.
    matrix_methods.set(
        "new",
        lua.create_function(|_, (nb_line, nb_col): (usize, usize)| {
            Ok(LuaMatrix(Matrix::new(nb_line, nb_col)))
        })?
    )?;

    matrix_methods.set(
        "newSquare",
        lua.create_function(|_, size: usize| {
            Ok(LuaMatrix(Matrix::new_square(size)))
        })?
    )?;

    matrix_methods.set(
        "newIdentity",
        lua.create_function(|_, size: usize| {
            Ok(LuaMatrix(Matrix::new_identity(size)))
        })?
    )?;

    // On place la table Matrix dans celle d'exports global.
    exports.set("Matrix", matrix_methods)?;

    // On renvoie la table d'exports.
    Ok(exports)
}

/// Wrapper du type matrix pour l'exporter vers lua.
#[derive(Clone)]
struct LuaMatrix(Matrix);

impl LuaUserData for LuaMatrix {
    fn add_methods<M: LuaUserDataMethods<Self>>(methods: &mut M) {
        // Getter/Setter
        methods.add_method("get", |_, this, (line, col): (usize, usize)| {
            Ok(this.0.get(line, col))
        });

        methods.add_method_mut("set", |_, this, (line, col, val): (usize, usize, f64)| {
            this.0.set(line, col, val);
            Ok(())
        });

        methods.add_method("getNbLine", |_, this, _: ()| {
            Ok(this.0.get_nb_line())
        });

        methods.add_method("getNbCol", |_, this, _: ()| {
            Ok(this.0.get_nb_col())
        });

        // Autres fonctions mathématiques pour les matrices.
        methods.add_method("transpose", |_, this, _: ()| {
            Ok(LuaMatrix(this.0.tranpose()))
        });

        methods.add_method("elementwiseMultiplication", |_, this, other: LuaAnyUserData| {
            let m = other.borrow::<LuaMatrix>()?;
            Ok(LuaMatrix(this.0.elementwise_multiplication(&m.0)))
        });

        methods.add_method("transposedMultiplication", |_, this, other: LuaAnyUserData| {
            let m = other.borrow::<LuaMatrix>()?;
            Ok(LuaMatrix(this.0.transposed_multiplication(&m.0)))
        });

        methods.add_method("multiplicationWithTransposed", |_, this, other: LuaAnyUserData| {
            let m = other.borrow::<LuaMatrix>()?;
            Ok(LuaMatrix(this.0.multiplication_with_transposed(&m.0)))
        });

        // Surcharge des opérateurs (méta méthodes).
        methods.add_meta_method(LuaMetaMethod::ToString, |_, this, ()| {
            let mut to_string = String::new();
            for i in 1..=this.0.get_nb_line() {
                for j in 1..=this.0.get_nb_col() {
                    to_string += &this.0.get(i, j).to_string();
                }

                if i != this.0.get_nb_line() {
                    to_string += "\n";
                }
            }

            Ok(to_string)
        });

        methods.add_meta_method(LuaMetaMethod::Add, |_, this, other: LuaAnyUserData| {
            let m = other.borrow::<LuaMatrix>()?;
            Ok(LuaMatrix(&this.0 + &m.0))
        });

        methods.add_meta_method(LuaMetaMethod::Mul, |_, this, other: LuaAnyUserData| {
            let m = other.borrow::<LuaMatrix>()?;
            Ok(LuaMatrix(&this.0 * &m.0))
        });
    }
}
