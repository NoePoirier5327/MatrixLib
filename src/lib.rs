use std::ops::{Add, AddAssign, Mul, MulAssign};

/// Type représentant une matrice de flottant de taille n par m.
/// Les indices de la matrice commencent à partir de 1.
#[derive(Debug, PartialEq)]
pub struct Matrix {
    nb_line: usize,
    nb_col: usize,
    content: Vec<f64>
}

impl Matrix {
    /// Construit une nouvelle matrice en choisissant son nombre de ligne
    /// et de colonne.
    ///
    /// # Arguments
    /// * `nb_line` nombre de ligne dans la nouvelle matrice.
    /// * `nb_col` nombre de colonne dans la nouvelle matrice.
    ///
    /// # Return
    /// Instance vers la nouvelle matrice remplie de 0f64.
    pub fn new(nb_line: usize, nb_col: usize) -> Self {
        assert!(nb_line >= 1 && nb_col >= 1, "You can't create a matrix that has no line or column.");

        Self {
            nb_line,
            nb_col,
            content: vec![0f64; nb_line * nb_col]
        }
    }

    /// Construit une nouvelle matrice carrée de la taille en paramètre.
    ///
    /// # Argument
    /// * `size` taille de la nouvelle matrice carrée.
    ///
    /// # Return
    /// Instance vers la nouvelle matrice carrée remplie de 0f64.
    pub fn new_square(size: usize) -> Self {
        Self::new(size, size)
    }

    /// Construit une nouvelle matrice identité de la taille en paramètre.
    ///
    /// # Argument
    /// * `size` taille de la nouvelle matrice identité.
    ///
    /// # Return
    /// Instance vers la nouvelle matrice identité.
    pub fn new_identity(size: usize) -> Self {
        let mut id = Self::new_square(size);

        for i in 1..=size {
            for j in 1..=size {
                if i == j {
                    id.set(i, j, 1f64);
                }
            }
        }

        id
    }

    /// Accesseur du contenu de la matrice.
    /// L'indexation commence à 1 et non 0.
    /// Lève une erreur si les indexs line et col ne sont pas 
    /// accessible.
    ///
    /// # Arguments
    /// * `line` index de la ligne à laquelle accéder.
    /// * `col` index de la colonne à laquelle accéder.
    ///
    /// # Return
    /// Valeur de la matrice à la position en paramètre.
    #[inline]
    pub fn get(&self, line: usize, col: usize) -> f64 {
        self.content[self.to_linear_coordinate(line, col)]
    }

    /// Mutateur du contenu de la matrice.
    /// L'indexation commence à 1 et non 0.
    /// Lève une erreur si les indexs line et col ne sont pas
    /// accessible.
    ///
    /// # Arguments
    /// * `line` index de la ligne à laquelle accéder.
    /// * `col` index de la colonne à laquelle accéder.
    /// * `value` valeur à attribuer à la matrice à la position en paramètre.
    #[inline]
    pub fn set(&mut self, line: usize, col: usize, value: f64) {
        let index = self.to_linear_coordinate(line, col);
        self.content[index] = value;
    }

    /// Accesseur du nombre de ligne de la matrice courante.
    #[inline]
    pub fn get_nb_line(&self) -> usize {
        self.nb_line
    }

    /// Accesseur du nombre de colonne de la matrice courante.
    #[inline]
    pub fn get_nb_col(&self) -> usize {
        self.nb_col
    }

    /// Calcul et renvoie la transposée de la matrice courante.
    pub fn tranpose(&self) -> Self {
        let mut m = Matrix::new(self.nb_col, self.nb_line);

        for i in 1..=m.get_nb_line() {
            for j in 1..=m.get_nb_col() {
                m.set(i, j, self.get(j, i));
            }
        }

        m
    }

    /// Affiche la matrice courante dans le terminal.
    pub fn disp(&self) {
        for i in 1..=self.nb_line {
            for j in 1..=self.nb_col {
                print!("{} ", self.get(i, j));
            }
            println!();
        }
    }

    /// Multiplie les deux matrices en paramètres termes à termes et renvoie le résultat dans une
    /// nouvelle matrice.
    ///
    /// # Arguments
    /// * `a` matrice à multiplier avec l'autre matrice en paramètre.
    /// * `b` matrice à multiplier avec l'autre matrice en paramètre.
    ///
    /// # Return
    /// Résultat de la multiplication termes à termes des deux matrices en paramètres.
    pub fn elementwise_multiplication(a: &Matrix, b: &Matrix) -> Matrix {
        assert_eq!(a.get_nb_line(), b.get_nb_line(), "The matrices should have the same sizes to multiply them.");
        assert_eq!(a.get_nb_col(), b.get_nb_col(), "The matrices should have the same sizes to multiply them.");

        let mut m = Matrix::new(a.get_nb_line(), a.get_nb_col());
        let total_size = m.get_nb_line() * m.get_nb_col();
        for i in 0..total_size {
            m.content[i] = a.content[i] * b.content[i];
        }

        m
    }

    /// Calcul et renvoie l'index dans content des indexs line et col.
    /// L'indexation de line et col commence à 1 et non 0, lève une erreur si ce n'est pas respecté.
    #[inline]
    fn to_linear_coordinate(&self, line: usize, col: usize) -> usize {
        assert!(line >= 1 && line <= self.nb_line, "Line index out of range.");
        assert!(col >= 1 && col <= self.nb_col, "Col index out of range.");
        (line - 1) * self.nb_col + (col - 1)
    }
}

/// Surcharge de l'opérateur + pour la somme de deux matrices.
/// Lève une erreur si elles n'ont pas la même taille.
impl Add for Matrix {
    type Output = Matrix;

    fn add(self, m: Matrix) -> Matrix {
        assert!(self.nb_line == m.nb_line, "Invalid dimensions for matrix sum.");
        assert!(self.nb_col == m.nb_col, "Invalid dimensions fo matrix sum.");

        let mut result = Matrix::new(self.nb_line, self.nb_col);

        let total_size = result.nb_line * result.nb_col;
        for i in 0..total_size {
            result.content[i] = self.content[i] + m.content[i];
        }

        result
    }
}

/// Surcharge de l'opérateur += pour la somme de deux matrices.
/// Lève une erreur si elles n'ont pas la même taille.
/// Le résultat de la somme est stocké dans la matrice à gauche de l'opérateur.
impl AddAssign for Matrix {
    fn add_assign(&mut self, m: Matrix) {
        assert!(self.nb_line == m.nb_line, "Invalid dimensions for matrix sum.");
        assert!(self.nb_col == m.nb_col, "Invalid dimensions for matrix sum.");

        let total_size = self.nb_line * self.nb_col;
        for i in 0..total_size {
            self.content[i] += m.content[i];
        }
    }
}

/// Surcharge de l'opérateur * pour le produit matricel.
/// Lève une erreur si self.nb_col != other.nb_line.
impl Mul for Matrix {
    type Output = Matrix;

    fn mul(self, m: Matrix) -> Matrix {
        assert!(self.nb_col == m.nb_line, "Invalid dimensions for matrix product.");

        let mut result = Matrix::new(self.nb_line, m.nb_col);
        for i in 1..=result.nb_line {
            for j in 1..=result.nb_col {
                for k in 1..=self.nb_col {
                    result.set(i, j, result.get(i, j) + (self.get(i, k) * m.get(k, j)));
                }
            }
        }

        result
    }
}

/// Surcharge de l'opérateur *= pour le produit matriciel.
/// Lève une erreur si self.nb_col != other.nb_line.
/// Le résultat est stocké dans la matrice à gauche de l'opérateur.
impl MulAssign for Matrix {
    fn mul_assign(&mut self, m: Matrix) {
        *self = self.clone() * m;
    }
}

/// Support du clonage d'une matrice quelconque.
impl Clone for Matrix {
    fn clone(&self) -> Self {
        Self {
            nb_line: self.nb_line,
            nb_col: self.nb_col,
            content: self.content.clone()
        }
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn is_equal() {
        let a = Matrix::new_square(3);
        let b = Matrix::new_square(3);
        assert_eq!(a, b);
    }

    #[test]
    fn is_not_equal() {
        let a = Matrix::new_square(3);
        let b = Matrix::new_identity(3);
        assert_ne!(a, b);
    }

    #[test]
    fn sum_null_with_identity() {
        let a = Matrix::new_square(5);
        let b = Matrix::new_identity(5);
        assert_eq!(a + b, Matrix::new_identity(5));
    }

    #[test]
    fn sum_then_assign() {
        let mut a = Matrix::new(2, 3);
        let mut b = Matrix::new(2, 3);
        let mut c = Matrix::new(2, 3);

        for i in 1..=2 {
            for j in 1..=3 {
                a.set(i, j, (i + j) as f64);
                b.set(i, j, (i + j) as f64);
                c.set(i, j, 2f64 * (i + j) as f64);
            }
        }

        a += b;
        assert_eq!(a, c);
    }

    #[test]
    fn product_with_identity() {
        let mut a = Matrix::new_square(3);
        let id = Matrix::new_identity(3);

        for i in 1..=3 {
            a.set(i, i, (i * i + i) as f64);
        }

        assert_eq!(a.clone() * id.clone(), a.clone());
        assert_eq!(id.clone() * a.clone(), a.clone());
    }

    #[test]
    fn product_then_assign() {
        let mut a = Matrix::new(2, 3);
        let mut b = Matrix::new(3, 1);
        let mut c = Matrix::new(2, 1);

        a.set(1, 1, 1_f64);
        a.set(1, 2, 2_f64);
        a.set(1, 3, 3_f64);
        a.set(2, 1, 4_f64);
        a.set(2, 2, 5_f64);
        a.set(2, 3, 6_f64);

        b.set(1, 1, 1_f64);
        b.set(2, 1, 2_f64);
        b.set(3, 1, 3_f64);

        c.set(1, 1, 14_f64);
        c.set(2, 1, 32_f64);

        a *= b;
        assert_eq!(a, c);
    }

    #[test]
    fn elementwise_multiplication() {
        let mut a = Matrix::new(3, 2);
        let mut c = Matrix::new(3, 2);

        for i in 1..=3 {
            a.set(i, 1, i as f64);
            a.set(i, 2, (i + 3) as f64);
            c.set(i, 1, (i * i) as f64);
            c.set(i, 2, ((i + 3) * (i + 3)) as f64);
        }

        let b = a.clone();
        assert_eq!(Matrix::elementwise_multiplication(&a, &b), c);
    }

    #[test]
    fn tranpose() {
        let mut a = Matrix::new(2, 3);
        let mut b = Matrix::new(3, 2);
        
        for i in 1..=3 {
            a.set(1, i, i as f64);
            a.set(2, i, (i + 3) as f64);
            b.set(i, 1, i as f64);
            b.set(i, 2, (i + 3) as f64);
        }

        assert_eq!(a.tranpose(), b);
    }
}
