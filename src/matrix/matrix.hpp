#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <cstddef>

/**
 * @class Matrix
 * @brief Représente une matrice composée de nombres en double précision.
 */
class Matrix {
  public:
    /**
     * @brief Construit une nouvelle matrice de largeur width et hauteur height.
     *
     * Elle l'initialise avec des 0.
     *
     * @param width largeur de la matrice à créer.
     * @param height hauteur de la matrice à créer.
     */
    Matrix(size_t width, size_t height);

    /**
     * @brief Détruit la matrice courante.
     */
    ~Matrix();

    /**
     * @brief Accesseur de la largeur de la matrice courante.
     *
     * @return Copie de la largeur de la matrice courante.
     */
    size_t get_width() const;

    /**
     * @brief Accesseur de la hauteur de la matrice courante.
     *
     * @return Copie de la hauteur de la matrice courante.
     */
    size_t get_height() const;

    /**
     * @brief Accesseur/Mutateur de la matrice courante.
     * 
     * @param x ligne de la matrice à récupérer.
     * @param y colonne de la matrice à récupérer.
     *
     * @return référence vers la valeur qu'on a voulu récupérer.
     *
     * @throw std::out_of_range si x et/ou y n'est pas accessible.
     */
    double& operator()(size_t x, size_t y);

    /**
     * @brief Accesseur de la matrice courante.
     *
     * @param x ligne de la matrice à récupérer.
     * @param y colonne de la matrice à récupérer.
     *
     * @return copie de la valeur à la position en paramètre.
     *
     * @throw std::out_of_range si x et/ou y n'est pas accessible.
     */
    double operator()(size_t x, size_t y) const;

    /**
     * @brief Calcul le produit matriciel entre celle courante et celle en paramètre.
     *
     * Surcharge l'opérateur `*` pour pouvoir calculer `matrice = A * B`
     *
     * @param m Matrice avec laquelle réaliser le produit matricel.
     *
     * @return Matrice résultante du produit.
     *
     * @throw std::invalid_argument si les dimensions ne permettent pas le produit matriciel.
     */
    Matrix operator*(const Matrix& m) const;

    /**
     * @brief Calcul la somme de deux matrices.
     *
     * Surcharge l'opérateur `+` pour pouvoir calculer `result = A + B`.
     * Le calcul se fait entre la matrice courante et celle en paramètre,
     * aucune n'est modifiée mais le résultat est renvoyée sous forme d'une nouvelle matrice.
     *
     * @param m Matrice avec laquelle réaliser la somme matriciel.
     *
     * @return Nouvelle matrice contenant le résultat de la somme.
     *
     * @throw std::invalid_argument si les dimensions ne permettent pas le calcul.
     */
    Matrix operator+(const Matrix& m) const;

  private:
    double *content;
    size_t width;
    size_t height;
};

#endif // !MATRIX_HEADER
