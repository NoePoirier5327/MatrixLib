#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <stdlib.h>

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

  private:
    double *content;
    size_t width;
    size_t height;
};

#endif // !MATRIX_HEADER
