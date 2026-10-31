--- @meta

--- @class Matrix
local Matrix = {}
Matrix.__index = Matrix

--- Construit une nouvelle matrice vide de taille nb_line par nb_col.
--- @param nbLine integer nombre de lignes de la matrice à créer.
--- @param nbCol integer nombre de colonnes de la matrice à créer.
--- @return Matrix instance vers la matrice qu'on vient de créer.
function Matrix.new(nbLine, nbCol) end

--- Construit une nouvelle matrice carrée vide de la taille size en paramètre.
--- @param size integer nombre lignes et de colonnes de la matrice à créer.
--- @return Matrix instance vers la matrice qu'on vient de créer.
function Matrix.newSquare(size) end

--- Construit une nouvelle matrice identitée de taille size.
--- @param size integer nombre de ligne et de colonnes de la matrice à créer.
--- @return Matrix instance vers la matrice qu'on vient de créer.
function Matrix.newIdentity(size) end

--- Accesseur dans la matrice courante.
--- @param line integer index de la ligne à laquelle accéder.
--- @param col integer index de la colonne à laquelle accéder.
--- @return number valeur stockée dans la matrice à la position en paramètre.
function Matrix:get(line, col) end

--- Mutateur de la matrice courante.
--- @param line integer index de la ligne à laquelle accéder.
--- @param col integer index de la ligne à laquelle accéder.
--- @param val number valeur à attribuer à la matrice courante.
function Matrix:set(line, col, val) end

--- Accesseur du nombre de ligne de la matrice courante.
--- @return integer nombre de ligne de la matrice courante.
function Matrix:getNbLine() end

--- Accesseur du nombre de colonne de la matrice courante.
--- @return integer nombre de colonne de la matrice courante.
function Matrix:getNbCol() end

--- Calcul la transposée de la matrice courante et la renvoie.
--- @return Matrix transposée de la matrice courante.
function Matrix:transpose() end

--- Méthode de multiplication termes à termes entre matrices.
--- @param m Matrix matrice à multiplier avec celle courante.
--- @return Matrix résultat de la multiplication termes à termes la matrice courante et celle en paramètre.
function Matrix:elementwiseMultiplication(m) end

--- Méthode de multiplication entre la matrice courante transposée et celle en paramètre.
--- @param m Matrix matrice à multiplier avec la transposée de la courante.
--- @return Matrix résultat du produit.
function Matrix:transposedMultiplication(m) end

--- Méthode de multiplication entre la matrice courante et la transposée de celle en paramètre.
--- @param m Matrix matrice dont la transposée sera multipliée avec la courante.
--- @return Matrix résultat du produit.
function Matrix:multiplicationWithTransposed(m) end

--- Métaméthode d'affichage de la matrice courante.
--- @return string chaine de caractères à afficher.
function Matrix:__tostring() end

--- Métaméthode de somme entre matrices.
--- @param m Matrix matrice à sommer avec celle courante.
--- @return Matrix résultat de la somme entre la matrice courante et celle en paramètre.
function Matrix:__add(m) end

--- Métaméthode de produit matriciel.
--- @param m Matrix matrice à multiplier à droite avec la matrice courante.
--- @return Matrix résultat du produit matriciel entre la matrie courante et celle en paramètre.
function Matrix:__mul(m) end

--- @field Matrix Matrix Matrice de flottant.
local Pokin = {}
Pokin.__index = Pokin

Pokin.Matrix = Matrix
return Pokin
