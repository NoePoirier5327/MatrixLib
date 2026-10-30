use mlua::prelude::*;

/// Point d'entré vers le module lua.
#[mlua::lua_module]
fn pokin(lua: &Lua) -> LuaResult<LuaTable> {
    let exports = lua.create_table()?;
    exports.set("hello", lua.create_function(hello)?)?;
    Ok(exports)
}

fn hello(_: &Lua, name: String) -> LuaResult<()> {
    println!("Hello {} !", name);
    Ok(())
}
