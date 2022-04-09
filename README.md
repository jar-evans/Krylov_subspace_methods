# Krylov subspace methods
Implementation of some methods to solve eigenvalue problem with the use of Krylov subspaces in C++.

## Background
The Krylov subspace is the space spanned by the set of vectors:

![equation](https://latex.codecogs.com/svg.image?K_n&space;=&space;\{\textbf{b},&space;A\textbf{b},&space;A^2\textbf{b},&space;...,&space;A^{n-1}\textbf{b}\})

![equation](https://latex.codecogs.com/svg.image?n&space;<&space;\mathrm{rank}(A))

Methods making use of these subspaces are most effective for large sparse matrices, as they use matrix-vector multiplication and the resulting subspace to search for solutions as opposed to normal matrix-matrix multiplication, which becomes very expensive for larger systems.

## Power method

This is the most simple method and is used to approximate the largest eigenvalue of a system, where the iteration is very simply:

![equation](https://latex.codecogs.com/svg.image?\textbf{x}_{i&plus;1}&space;=&space;A\textbf{x}_i)

This comes from the idea that ![equation](https://latex.codecogs.com/svg.image?\inline&space;A^{n-1}\textbf{b}) approximates the dominant eigenvector. Therefore, the dominant eigenvalue comes from the Rayleigh quotient:

![equation](https://latex.codecogs.com/svg.image?\inline&space;\lambda[\textbf{x}_i]&space;=&space;\frac{\textbf{x}_i^TA\textbf{x}_i}{\textbf{x}_i^T\textbf{x}_i}&space;=&space;\frac{\textbf{x}_{i&plus;1}^TA\textbf{x}_i}{\textbf{x}_i^T\textbf{x}_i})

### Inverse power method*

Where the power method estimates the largest eigenvalue of ![equation](https://latex.codecogs.com/svg.image?\inline&space;A), the inverse power method estimates the smallest eigenvalue of ![equation](https://latex.codecogs.com/svg.image?\inline&space;A). The only extra step is to invert ![equation](https://latex.codecogs.com/svg.image?\inline&space;A), such that the iteration becomes:

![equation](https://latex.codecogs.com/svg.image?\textbf{x}_{i&plus;1}&space;=&space;A^{-1}\textbf{x}_i)

and then the eigenvalue can be extracted from the converged to eigenvector via the Rayleigh quotient as before.

### Shifted inverse method*

Here the iteration intends to converge to the eigenvalue closest to the given value, ![equation](https://latex.codecogs.com/svg.image?\inline&space;s):

![equation](https://latex.codecogs.com/svg.image?\inline&space;\textbf{x}_{i&plus;1}&space;=&space;(A&space;-&space;sI)^{-1}\textbf{x}_i)

Where the inverse power method operates for ![equation](https://latex.codecogs.com/svg.image?\inline&space;s) = 0. Further, finding the inverse of large matrices is not the most pleasant task, therefore typically the approach is to solve the following linear system.

![equation](https://latex.codecogs.com/svg.image?\inline&space;(A&space;-&space;sI)\textbf{x}_{i&plus;1}&space;=&space;\textbf{x}_i)

Naturally the better the guess of ![equation](https://latex.codecogs.com/svg.image?\inline&space;s), the faster the convergence. This means in some cases that it is more efficient to update ![equation](https://latex.codecogs.com/svg.image?\inline&space;s) with the Rayleigh quotient and 'restart' the iteration, instead of sticking with the same ![equation](https://latex.codecogs.com/svg.image?\inline&space;(A&space;-&space;sI)) until convergence.

### Orthogonal iteration*

#TODO

## Lanczos iteration

A specific form of the Arnoldi method, for when ![equation](https://latex.codecogs.com/svg.image?\inline&space;A) is Hermitian (square matrix which is equal to the conjugate transpose of itself).

The purpose of Lanczos is to reduce the hermitian matrix to a smaller tri-diagonal matrix, for which the eigenpairs can be readily found via another method (QR is common). However, this only works if the eigenpairs of ![equation](https://latex.codecogs.com/svg.image?\inline&space;T_n) approximate those of ![equation](https://latex.codecogs.com/svg.image?\inline&space;A) (which isn't actually guarunteed as Lanczos is known to have problems with rounding errors that lead to loss of orthogonality).

## Bi-Lanczos iteration*

#TODO

## Arnoldi iteration**

Arnoldi (just like Lanczos) reduces ![equation](https://latex.codecogs.com/svg.image?\inline&space;A) to a smaller matrix that can be fed into simple methods to approximate the eigenpairs corresponding to the largest eigenvalues of ![equation](https://latex.codecogs.com/svg.image?\inline&space;A).

This smaller matrix, in the case of Arnoldi, is ![equation](https://latex.codecogs.com/svg.image?\inline&space;H_n), a upper Hessenberg matrix:

![equation](https://latex.codecogs.com/svg.image?\inline&space;H_n&space;=&space;Q_n^{\dagger}AQ_n)

where ![equation](https://latex.codecogs.com/svg.image?\inline&space;H_n) is actually the projection of ![equation](https://latex.codecogs.com/svg.image?\inline&space;A) onto the Krylov subspace ![equation](https://latex.codecogs.com/svg.image?\inline&space;K_n). ![equation](https://latex.codecogs.com/svg.image?\inline&space;Q_n) is the n-order orthogonal Krylov basis used to map ![equation](https://latex.codecogs.com/svg.image?\inline&space;A) to ![equation](https://latex.codecogs.com/svg.image?\inline&space;H_n).

With each iteration of Arnoldi, a new basis vector of the Krylov subspace orthogonalised wrt the other basis vectors is added to ![equation](https://latex.codecogs.com/svg.image?\inline&space;Q_n). Arnoldi can be restarted in the case the subspace being generated starts to become too large.

## Sources

W. Ford. Numerical Linear Algebra with Applications. Academic Press, 2015

B.N. Parlett. The Symmetric Eigenvalue Problem. Classics in Applied Mathematics 20. SIAM, Philadelphia, 1998

Yousef Saad. Numerical Methods for Large Eigenvalue Problems. Manchester University Press, 1992.

D.V. Fedorov. Yet Another Introduction to Numerical Methods. https://phys.au.dk/~fedorov/Numeric/Book/book.pdf, 2013



\* Not implemented

** Could potentially maybe possibly still need some fine tuning
