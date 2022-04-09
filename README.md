# Krylov subspace methods
Implementation of some methods to solve eigenvalue problem with the use of Krylov subspaces in C++.

Methods making use of these subspaces are most effective for large sparse matrices, as they use matrix-vector multiplication and the resulting subspace over normal matrix-matrix multiplication, which becomes very expensive for larger systems.

## Power method

### Inverse power method

### Orthogonal iteration

## Lanczos method

## Bi-Lanczos method

## Arnoldi method


## Sources

B.N. Parlett. The Symmetric Eigenvalue Problem. Classics in Applied Mathematics 20. SIAM, Philadelphia, 1998

Yousef Saad, Numerical Methods for Large Eigenvalue Problems, Manchester University Press, 1992.

D.V. Fedorov. Yet Another Introduction to Numerical Methods. https://phys.au.dk/~fedorov/Numeric/Book/book.pdf, 2013
