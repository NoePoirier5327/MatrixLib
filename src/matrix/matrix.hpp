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
     * @brief Constructeur de copie
     *
     * Copie le contenu de la matrice en paramètre pour créer le contenu
     * de la nouvelle instance.
     *
     * @param m Copie cette matrice pour créer une nouvelle instance.
     */
    Matrix(const Matrix& m);

    /**
     * @brief Constructeur de déplacement.
     *
     * Transfère le contenu de la matrice en paramètre dans la nouvelle instance.
     *
     * @param m Matrice dont le contenu est à transférer.
     */
    Matrix(Matrix&& m) noexcept;

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
     * @brief Comparateur de deux matrices.
     *
     * @param m Seconde matrice à comparer.
     *
     * @return true si elle sont identique, false sinon
     *
     * @note si les deux matrices ont des dimensions différentes, alors, la comparaison renvoie faux.
     */
    bool operator==(const Matrix& m) const;

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

    /**
     * @brief Copie la matrice en paramètre dans la matrice courante.
     *
     * Surcharge l'opérateur `=`, la méthode désalloue la matrice courante
     * et copie le contenu de la matrice en paramètre dans celle courante.
     *
     * @param m Matrice à copier.
     *
     * @return Référence vers l'instance de la matrice à attribuer.
     */
    Matrix& operator=(const Matrix& m);

    /**
     * @brief Transfère la matrice en paramètre dans la matrice courante.
     *
     * Surcharge l'opérateur `=`, la méthode transfère le contenu de la matrice
     * en paramètre dans la matrice en paramètre.
     *
     * @param m Matrice à transférer.
     *
     * @return Référence vers l'instance de la matrice à attribuer.
     */
    Matrix& operator=(Matrix&& m) noexcept;

    /**
     * @brief Affiche la matrice courante.
     */
    void display() const;

  private:
    double *content;
    size_t width;
    size_t height;
};

/**
 * @brief Créer une matrice identitée de taille n.
 *
 * @param n taille de la matrice à créer.
 *
 * @return Instance de la matrice identitée.
 */
Matrix new_identity_matrix(size_t n);

#endif // !MATRIX_HEADER
