#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

int nextPowerOfTwo(int n) {
    int p = 1;
    while (p < n) {
        p <<= 1;
    }
    return p;
}

int** allocateMatrix(int n) {
    int** M = new int*[n];
    for (int i = 0; i < n; ++i) {
        M[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            M[i][j] = 0;
        }
    }
    return M;
}

void freeMatrix(int** M, int n) {
    if (M == nullptr) {
        return;
    }
    for (int i = 0; i < n; ++i) {
        delete[] M[i];
    }
    delete[] M;
}

void copySubmatrix(int** src, int srcRow, int srcCol, int** dst, int m) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            dst[i][j] = src[srcRow + i][srcCol + j];
        }
    }
}

void placeSubmatrix(int** src, int** dst, int dstRow, int dstCol, int m) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            dst[dstRow + i][dstCol + j] = src[i][j];
        }
    }
}

void addMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void writeNxN(const char* filename, int** M, int n) {
    std::ofstream out(filename);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << M[i][j];
            if (j + 1 < n) {
                out << ' ';
            }
        }
        out << '\n';
    }
}

void divideAndConquer(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int m = n / 2;

    int** A11 = allocateMatrix(m);
    int** A12 = allocateMatrix(m);
    int** A21 = allocateMatrix(m);
    int** A22 = allocateMatrix(m);
    int** B11 = allocateMatrix(m);
    int** B12 = allocateMatrix(m);
    int** B21 = allocateMatrix(m);
    int** B22 = allocateMatrix(m);

    copySubmatrix(A, 0, 0, A11, m);
    copySubmatrix(A, 0, m, A12, m);
    copySubmatrix(A, m, 0, A21, m);
    copySubmatrix(A, m, m, A22, m);
    copySubmatrix(B, 0, 0, B11, m);
    copySubmatrix(B, 0, m, B12, m);
    copySubmatrix(B, m, 0, B21, m);
    copySubmatrix(B, m, m, B22, m);

    int** P1 = allocateMatrix(m);
    int** P2 = allocateMatrix(m);
    int** C11 = allocateMatrix(m);
    int** C12 = allocateMatrix(m);
    int** C21 = allocateMatrix(m);
    int** C22 = allocateMatrix(m);

    divideAndConquer(A11, B11, P1, m);
    divideAndConquer(A12, B21, P2, m);
    addMatrix(P1, P2, C11, m);

    divideAndConquer(A11, B12, P1, m);
    divideAndConquer(A12, B22, P2, m);
    addMatrix(P1, P2, C12, m);

    divideAndConquer(A21, B11, P1, m);
    divideAndConquer(A22, B21, P2, m);
    addMatrix(P1, P2, C21, m);

    divideAndConquer(A21, B12, P1, m);
    divideAndConquer(A22, B22, P2, m);
    addMatrix(P1, P2, C22, m);

    placeSubmatrix(C11, C, 0, 0, m);
    placeSubmatrix(C12, C, 0, m, m);
    placeSubmatrix(C21, C, m, 0, m);
    placeSubmatrix(C22, C, m, m, m);

    freeMatrix(A11, m);
    freeMatrix(A12, m);
    freeMatrix(A21, m);
    freeMatrix(A22, m);
    freeMatrix(B11, m);
    freeMatrix(B12, m);
    freeMatrix(B21, m);
    freeMatrix(B22, m);
    freeMatrix(P1, m);
    freeMatrix(P2, m);
    freeMatrix(C11, m);
    freeMatrix(C12, m);
    freeMatrix(C21, m);
    freeMatrix(C22, m);
}

void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int m = n / 2;

    int** A11 = allocateMatrix(m);
    int** A12 = allocateMatrix(m);
    int** A21 = allocateMatrix(m);
    int** A22 = allocateMatrix(m);
    int** B11 = allocateMatrix(m);
    int** B12 = allocateMatrix(m);
    int** B21 = allocateMatrix(m);
    int** B22 = allocateMatrix(m);

    copySubmatrix(A, 0, 0, A11, m);
    copySubmatrix(A, 0, m, A12, m);
    copySubmatrix(A, m, 0, A21, m);
    copySubmatrix(A, m, m, A22, m);
    copySubmatrix(B, 0, 0, B11, m);
    copySubmatrix(B, 0, m, B12, m);
    copySubmatrix(B, m, 0, B21, m);
    copySubmatrix(B, m, m, B22, m);

    int** T1 = allocateMatrix(m);
    int** T2 = allocateMatrix(m);
    int** M1 = allocateMatrix(m);
    int** M2 = allocateMatrix(m);
    int** M3 = allocateMatrix(m);
    int** M4 = allocateMatrix(m);
    int** M5 = allocateMatrix(m);
    int** M6 = allocateMatrix(m);
    int** M7 = allocateMatrix(m);

    addMatrix(A11, A22, T1, m);
    addMatrix(B11, B22, T2, m);
    strassen(T1, T2, M1, m);

    addMatrix(A21, A22, T1, m);
    strassen(T1, B11, M2, m);

    subtractMatrix(B12, B22, T2, m);
    strassen(A11, T2, M3, m);

    subtractMatrix(B21, B11, T2, m);
    strassen(A22, T2, M4, m);

    addMatrix(A11, A12, T1, m);
    strassen(T1, B22, M5, m);

    subtractMatrix(A21, A11, T1, m);
    addMatrix(B11, B12, T2, m);
    strassen(T1, T2, M6, m);

    subtractMatrix(A12, A22, T1, m);
    addMatrix(B21, B22, T2, m);
    strassen(T1, T2, M7, m);

    int** C11 = allocateMatrix(m);
    int** C12 = allocateMatrix(m);
    int** C21 = allocateMatrix(m);
    int** C22 = allocateMatrix(m);

    addMatrix(M1, M4, T1, m);
    subtractMatrix(T1, M5, T2, m);
    addMatrix(T2, M7, C11, m);

    addMatrix(M3, M5, C12, m);

    addMatrix(M2, M4, C21, m);

    subtractMatrix(M1, M2, T1, m);
    addMatrix(T1, M3, T2, m);
    addMatrix(T2, M6, C22, m);

    placeSubmatrix(C11, C, 0, 0, m);
    placeSubmatrix(C12, C, 0, m, m);
    placeSubmatrix(C21, C, m, 0, m);
    placeSubmatrix(C22, C, m, m, m);

    freeMatrix(A11, m);
    freeMatrix(A12, m);
    freeMatrix(A21, m);
    freeMatrix(A22, m);
    freeMatrix(B11, m);
    freeMatrix(B12, m);
    freeMatrix(B21, m);
    freeMatrix(B22, m);
    freeMatrix(T1, m);
    freeMatrix(T2, m);
    freeMatrix(M1, m);
    freeMatrix(M2, m);
    freeMatrix(M3, m);
    freeMatrix(M4, m);
    freeMatrix(M5, m);
    freeMatrix(M6, m);
    freeMatrix(M7, m);
    freeMatrix(C11, m);
    freeMatrix(C12, m);
    freeMatrix(C21, m);
    freeMatrix(C22, m);
}

void naiveMultiply(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sum = 0;
            for (int k = 0; k < n; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

void strassenCutoff(int** A, int** B, int** C, int n, int cutoff) {
    if (n <= cutoff) {
        naiveMultiply(A, B, C, n);
        return;
    }

    int m = n / 2;

    int** A11 = allocateMatrix(m);
    int** A12 = allocateMatrix(m);
    int** A21 = allocateMatrix(m);
    int** A22 = allocateMatrix(m);
    int** B11 = allocateMatrix(m);
    int** B12 = allocateMatrix(m);
    int** B21 = allocateMatrix(m);
    int** B22 = allocateMatrix(m);

    copySubmatrix(A, 0, 0, A11, m);
    copySubmatrix(A, 0, m, A12, m);
    copySubmatrix(A, m, 0, A21, m);
    copySubmatrix(A, m, m, A22, m);
    copySubmatrix(B, 0, 0, B11, m);
    copySubmatrix(B, 0, m, B12, m);
    copySubmatrix(B, m, 0, B21, m);
    copySubmatrix(B, m, m, B22, m);

    int** T1 = allocateMatrix(m);
    int** T2 = allocateMatrix(m);
    int** M1 = allocateMatrix(m);
    int** M2 = allocateMatrix(m);
    int** M3 = allocateMatrix(m);
    int** M4 = allocateMatrix(m);
    int** M5 = allocateMatrix(m);
    int** M6 = allocateMatrix(m);
    int** M7 = allocateMatrix(m);

    addMatrix(A11, A22, T1, m);
    addMatrix(B11, B22, T2, m);
    strassenCutoff(T1, T2, M1, m, cutoff);

    addMatrix(A21, A22, T1, m);
    strassenCutoff(T1, B11, M2, m, cutoff);

    subtractMatrix(B12, B22, T2, m);
    strassenCutoff(A11, T2, M3, m, cutoff);

    subtractMatrix(B21, B11, T2, m);
    strassenCutoff(A22, T2, M4, m, cutoff);

    addMatrix(A11, A12, T1, m);
    strassenCutoff(T1, B22, M5, m, cutoff);

    subtractMatrix(A21, A11, T1, m);
    addMatrix(B11, B12, T2, m);
    strassenCutoff(T1, T2, M6, m, cutoff);

    subtractMatrix(A12, A22, T1, m);
    addMatrix(B21, B22, T2, m);
    strassenCutoff(T1, T2, M7, m, cutoff);

    int** C11 = allocateMatrix(m);
    int** C12 = allocateMatrix(m);
    int** C21 = allocateMatrix(m);
    int** C22 = allocateMatrix(m);

    addMatrix(M1, M4, T1, m);
    subtractMatrix(T1, M5, T2, m);
    addMatrix(T2, M7, C11, m);

    addMatrix(M3, M5, C12, m);
    addMatrix(M2, M4, C21, m);

    subtractMatrix(M1, M2, T1, m);
    addMatrix(T1, M3, T2, m);
    addMatrix(T2, M6, C22, m);

    placeSubmatrix(C11, C, 0, 0, m);
    placeSubmatrix(C12, C, 0, m, m);
    placeSubmatrix(C21, C, m, 0, m);
    placeSubmatrix(C22, C, m, m, m);

    freeMatrix(A11, m);
    freeMatrix(A12, m);
    freeMatrix(A21, m);
    freeMatrix(A22, m);
    freeMatrix(B11, m);
    freeMatrix(B12, m);
    freeMatrix(B21, m);
    freeMatrix(B22, m);
    freeMatrix(T1, m);
    freeMatrix(T2, m);
    freeMatrix(M1, m);
    freeMatrix(M2, m);
    freeMatrix(M3, m);
    freeMatrix(M4, m);
    freeMatrix(M5, m);
    freeMatrix(M6, m);
    freeMatrix(M7, m);
    freeMatrix(C11, m);
    freeMatrix(C12, m);
    freeMatrix(C21, m);
    freeMatrix(C22, m);
}

void fillRandom(int** M, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            M[i][j] = (std::rand() % 21) - 10;
        }
    }
}

int runMandatory() {
    std::ifstream in("input.txt");
    if (!in) {
        return 1;
    }

    int n = 0;
    in >> n;
    if (n <= 0) {
        return 1;
    }

    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> A[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> B[i][j];
        }
    }
    in.close();

    int N = nextPowerOfTwo(n);
    int** Ap = allocateMatrix(N);
    int** Bp = allocateMatrix(N);
    int** C1 = allocateMatrix(N);
    int** C2 = allocateMatrix(N);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Ap[i][j] = A[i][j];
            Bp[i][j] = B[i][j];
        }
    }

    clock_t start1 = clock();
    divideAndConquer(Ap, Bp, C1, N);
    clock_t end1 = clock();

    clock_t start2 = clock();
    strassen(Ap, Bp, C2, N);
    clock_t end2 = clock();

    writeNxN("output_m1.txt", C1, n);
    writeNxN("output_m2.txt", C2, n);

    std::ofstream q3("output_q3.txt");
    q3 << static_cast<int>(end1 - start1) << ' ' << static_cast<int>(end2 - start2)
       << '\n';

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(Ap, N);
    freeMatrix(Bp, N);
    freeMatrix(C1, N);
    freeMatrix(C2, N);
    return 0;
}

int runExtraCredit() {
    const int n = 128;
    const int minH = 3;
    const int maxH = 7;
    std::srand(538);

    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    int** C = allocateMatrix(n);
    int** Cref = allocateMatrix(n);
    fillRandom(A, n);
    fillRandom(B, n);

    clock_t naiveStart = clock();
    naiveMultiply(A, B, Cref, n);
    clock_t naiveEnd = clock();
    int naiveTime = static_cast<int>(naiveEnd - naiveStart);

    std::ofstream out("extra_credit_times.txt");
    out << "n " << n << '\n';
    out << "naive " << naiveTime << '\n';
    out << "h cutoff_size strassen_time\n";

    for (int h = minH; h <= maxH; ++h) {
        int cutoff = 1 << h;
        clock_t start = clock();
        strassenCutoff(A, B, C, n, cutoff);
        clock_t end = clock();
        int t = static_cast<int>(end - start);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (C[i][j] != Cref[i][j]) {
                    freeMatrix(A, n);
                    freeMatrix(B, n);
                    freeMatrix(C, n);
                    freeMatrix(Cref, n);
                    return 1;
                }
            }
        }
        out << h << ' ' << cutoff << ' ' << t << '\n';
    }

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);
    freeMatrix(Cref, n);
    return 0;
}

int main(int argc, char** argv) {
    if (argc >= 2 && argv[1][0] == '-' && argv[1][1] == '-' &&
        argv[1][2] == 'e') {
        return runExtraCredit();
    }
    return runMandatory();
}
