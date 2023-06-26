#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int exit_status = OK;
  if (A == NULL) return INCORRECT;
  if (A->rows == A->columns && A->rows > 0) {
    double det = 0.0;
    matrix_t minor = {0};

    if (A->rows == 1) {
      det = A->matrix[0][0];
    } else if (A->rows == 2) {
      det =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      for (int j = 0; j < A->rows; j++) {
        exit_status = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
        if (exit_status == OK) {
          for (int i = 1; i < A->rows; i++) {
            for (int k = 0; k < A->columns - 1; k++) {
              if (k < j) {
                minor.matrix[i - 1][k] = A->matrix[i][k];
              } else {
                minor.matrix[i - 1][k] = A->matrix[i][k + 1];
              }
            }
          }
          double minor_det = 0.0;
          exit_status = s21_determinant(&minor, &minor_det);
          if (exit_status == OK) {
            int sign = ((j + 1) % 2 == 0) ? -1 : 1;
            det += sign * A->matrix[0][j] * minor_det;
          }
          s21_remove_matrix(&minor);
        }
      }
    }
    *result = det;
  } else
    exit_status = CALC_ERROR;
  return exit_status;
}