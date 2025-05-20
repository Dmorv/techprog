#include <iostream>
#include <cstring>

class vect {
public:
    int dim;
    double* b;
    int num;
    static int count;

    vect(int d = 3) {
        dim = d;
        b = new double[dim];
        for (int i = 0; i < dim; ++i) b[i] = 0;
        count++;
        num = count;
        std::cout << "Создан вектор #" << num << std::endl;
    }

    vect(const vect& v) {
        dim = v.dim;
        b = new double[dim];
        for (int i = 0; i < dim; ++i) b[i] = v.b[i];
        count++;
        num = count;
        std::cout << "Скопирован вектор #" << v.num << " в вектор #" << num << std::endl;
    }

    ~vect() {
        std::cout << "Удалён вектор #" << num << std::endl;

        delete[] b;
    }

    vect& operator=(const vect& v) {
        if (this == &v) return *this;
        delete[] b;
        dim = v.dim;
        b = new double[dim];
        for (int i = 0; i < dim; ++i) b[i] = v.b[i];
        std::cout << "Присвоен вектор #" << v.num << " вектору #" << num << std::endl;
        return *this;
    }

    vect operator+(const vect& v) {
        vect res(dim);
        for (int i = 0; i < dim; ++i)
            res.b[i] = b[i] + v.b[i];
        std::cout << "Сложение векторов #" << num << " и #" << v.num << std::endl;
        return res;
    }

    vect operator-(const vect& v) {
        vect res(dim);
        for (int i = 0; i < dim; ++i)
            res.b[i] = b[i] - v.b[i];
        std::cout << "Вычитание векторов #" << num << " и #" << v.num << std::endl;
        return res;
    }

    vect operator-() {
        vect res(dim);
        for (int i = 0; i < dim; ++i)
            res.b[i] = -b[i];
        std::cout << "Унарный минус вектора #" << num << std::endl;
        return res;
    }

    double operator*(const vect& v) {
        double sum = 0;
        for (int i = 0; i < dim; ++i)
            sum += b[i] * v.b[i];
        std::cout << "Скалярное произведение векторов #" << num << " и #" << v.num << std::endl;
        return sum;
    }

    friend vect operator*(double k, const vect& v) {
        vect res(v.dim);
        for (int i = 0; i < v.dim; ++i)
            res.b[i] = k * v.b[i];
        std::cout << "Умножение вектора #" << v.num << " на число " << k << std::endl;
        return res;
    }

    void print() const {
        std::cout << "Вектор #" << num << ": ";
        for (int i = 0; i < dim; ++i)
            std::cout << b[i] << " ";
        std::cout << std::endl;
    }
};

int vect::count = 0;
class matr {
    public:
        int dim;
        double** a;
        int num;
        static int count;
    
        matr(int d = 3) {
            dim = d;
            a = new double*[dim];         // создаём массив указателей (строк)
            for (int i = 0; i < dim; ++i)
                a[i] = new double[dim];   // создаём каждую строку
            for (int i = 0; i < dim; ++i)
                for (int j = 0; j < dim; ++j)
                    a[i][j] = 0;
            count++;
            num = count;
            std::cout << "Создана матрица #" << num << std::endl;
        }
    
        matr(const matr& m) {
            dim = m.dim;
            a = new double*[dim];
            for (int i = 0; i < dim; ++i) {
                a[i] = new double[dim];
                for (int j = 0; j < dim; ++j)
                    a[i][j] = m.a[i][j];
            }
            count++;
            num = count;
            std::cout << "Скопирована матрица #" << m.num << " в матрицу #" << num << std::endl;
        }
    
        ~matr() {
            for (int i = 0; i < dim; ++i)
                delete[] a[i];   // удаляем каждую строку
            delete[] a;          // удаляем массив указателей
            std::cout << "Удалена матрица #" << num << std::endl;
        }
    
        matr& operator=(const matr& m) {
            if (this == &m) return *this;
    
            for (int i = 0; i < dim; ++i)
                delete[] a[i];
            delete[] a;
    
            dim = m.dim;
            a = new double*[dim];
            for (int i = 0; i < dim; ++i) {
                a[i] = new double[dim];
                for (int j = 0; j < dim; ++j)
                    a[i][j] = m.a[i][j];
            }
            std::cout << "Присвоена матрица #" << m.num << " матрице #" << num << std::endl;
            return *this;
        }
    
        matr operator+(const matr& m) {
            matr res(dim);
            for (int i = 0; i < dim; ++i)
                for (int j = 0; j < dim; ++j)
                    res.a[i][j] = a[i][j] + m.a[i][j];
            std::cout << "Сложение матриц #" << num << " и #" << m.num << std::endl;
            return res;
        }
    
        matr operator-(const matr& m) {
            matr res(dim);
            for (int i = 0; i < dim; ++i)
                for (int j = 0; j < dim; ++j)
                    res.a[i][j] = a[i][j] - m.a[i][j];
            std::cout << "Вычитание матриц #" << num << " и #" << m.num << std::endl;
            return res;
        }
    
        matr operator-() {
            matr res(dim);
            for (int i = 0; i < dim; ++i)
                for (int j = 0; j < dim; ++j)
                    res.a[i][j] = -a[i][j];
            std::cout << "Унарный минус матрицы #" << num << std::endl;
            return res;
        }
    
        matr operator*(const matr& m) {
            matr res(dim);
            for (int i = 0; i < dim; ++i)
                for (int j = 0; j < dim; ++j) {
                    res.a[i][j] = 0;
                    for (int k = 0; k < dim; ++k)
                        res.a[i][j] += a[i][k] * m.a[k][j];
                }
            std::cout << "Умножение матриц #" << num << " и #" << m.num << std::endl;
            return res;
        }
    
        matr operator*(double k) {
            matr res(dim);
            for (int i = 0; i < dim; ++i)
                for (int j = 0; j < dim; ++j)
                    res.a[i][j] = k * a[i][j];
            std::cout << "Умножение матрицы #" << num << " на число " << k << std::endl;
            return res;
        }
    
        vect operator*(const vect& v) {
            vect res(dim);
            for (int i = 0; i < dim; ++i) {
                res.b[i] = 0;
                for (int j = 0; j < dim; ++j)
                    res.b[i] += a[i][j] * v.b[j];
            }
            std::cout << "Умножение матрицы #" << num << " на вектор #" << v.num << std::endl;
            return res;
        }
    
        void print() const {
            std::cout << "Матрица #" << num << ":" << std::endl;
            for (int i = 0; i < dim; ++i) {
                for (int j = 0; j < dim; ++j)
                    std::cout << a[i][j] << " ";
                std::cout << std::endl;
            }
        }
    };
    

int matr::count = 0;

int main() {
    vect v1(3), v2(3);
    v1.b[0] = 1; v1.b[1] = 2; v1.b[2] = 3;
    v2.b[0] = 4; v2.b[1] = 5; v2.b[2] = 6;

    vect v3 = v1 + v2;
    v3.print();

    vect v4 = -v1;
    v4.print();

    double scalar = v1 * v2;
    std::cout << "Скалярное произведение: " << scalar << std::endl;

    vect v5 = 2 * v1;
    v5.print();

    matr m1(3), m2(3);
    for (int i = 0; i < 9; ++i) 
        for (int j = 0; i < 3; i++){
            m1.a[i][j] = i + 1;
            m2.a[i][j] = (i + 1) * 2;
    }

    matr m3 = m1 + m2;
    m3.print();

    matr m4 = m1 * m2;
    m4.print();

    vect v6 = m1 * v1;
    v6.print();

    return 0;
}