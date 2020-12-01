#include <Matrix/matrix.hpp>


/*konstruktor dla macierzy*/

Matrix::Matrix(int n, int m){
    row = n;
    columns = m;
    cout<<"Tworzenie macierzy "<<row<<"x"<<columns<<endl;
    matrix.resize(row); // tworzymy odpowiedni liczbe wierszy w wektorze
    for(int i = 0; i < row; i++){
        matrix[i].resize(columns, 0); // w każdym wierszu towrzymy odpowiednią lizbe kolumn i każde miejsce wypełniamy zerami
    }
}

/* konstruktor dla macierzy kwadratowej */

Matrix::Matrix(int n){
    row = n;
    columns = n;
    cout<<"Tworzenie macierzy "<<row<<"x"<<columns<<endl;
    matrix.resize(row); // tworzymy odpowiedni liczbe wierszy w wektorze
    for(int i = 0; i < row; i++){
        matrix[i].resize(columns, 0); // w każdym wierszu towrzymy odpowiednią lizbe kolumn i każde miejsce wypełniamy zerami
    }
}

/*konstruktor dla macierzy z pliku*/

Matrix::Matrix(string path){
    ifstream file;
    file.open(path);
    if(file.is_open()){
        file >> row;
        file >> columns;
        cout<<"Tworzenie macierzy "<<row<<"x"<<columns<<endl;
        matrix.resize(row); // tworzymy odpowiedni liczbe wierszy w wektorze
        for(int i = 0; i < row; i++){
            matrix[i].resize(columns); // w każdym wierszu towrzymy odpowiednią liczbe kolumn
        }
        // wypelnienie tablicy
        for(int i = 0; i < row; i++){
            for(int j = 0; j < columns; j++){
                file >> matrix[i][j];
            }
        }   
        
        file.close();
    }else cout<<"Blad. Plik nie zostal otwarty"<<endl;
}

/*drukowanie macierzy na ekran */

void Matrix::print(){
    cout<<"Wyswietlanie macierzy "<<row<<"x"<<columns<<endl;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < columns; j++){
            cout<<matrix[i][j]<<"  ";
        }
        cout<<endl;
    }
}

/* Pobieranie elem. (n, m)*/

double Matrix::get(int n, int m){
    // sprawdzanie czy elem. (n, m) istnieje
    if((n < 0 || n >= row) || (m < 0 || m >= columns)){
        cout<<"Element ("<<n<<", "<<m<<") nie istnieje dla macierzy "<<row<<"x"<<columns<<endl;
        exit(1);
    }
    return matrix[n][m];
}

/*ustawianie wart. elem. (n, m) na val*/

void Matrix::set(int n, int m, double val){
    if((n < 0 || n >= row) || (m < 0 || m >= columns)){
        cout<<"Element ("<<n<<", "<<m<<") nie istnieje dla macierzy "<<row<<"x"<<columns<<endl;
        exit(1);
    }
    cout<<"Ustawianie wartosci " <<val<<" dla elementu ("<<n<<", "<<m<<") dla macierzy "<<row<<"x"<<columns<<endl;
    matrix[n][m] = val;
}

/*metody zwracajace odpowiednio liczbe kolumn i wierszy*/

int Matrix::cols(){
    return columns;
}

int Matrix::rows(){
    return row;
}

/*Działania na macierzach:
-dodawanie
-odejmowanie
-mnożenie */

Matrix Matrix::add(Matrix m2){
    if(row == m2.rows() && columns == m2.cols()){
        Matrix matrix_sum(row, columns);
        for(int i = 0; i < row; i++){
            for(int j = 0; j < columns; j++){
                matrix_sum.matrix[i][j] = matrix[i][j] + m2.matrix[i][j];
            }
        }
        return matrix_sum;

    }else exit(1);    
}

Matrix Matrix::subtract(Matrix m2){
    if(row == m2.rows() && columns == m2.cols()){
        Matrix matrix_sub(row, columns);
        for(int i = 0; i < row; i++){
            for(int j = 0; j < columns; j++){
                matrix_sub.matrix[i][j] = matrix[i][j] - m2.matrix[i][j];
            }
        }
        return matrix_sub;
    }else exit(1);  
}

Matrix Matrix::multiply(Matrix m2){
    if(columns == m2.rows()){
        Matrix matrix_mul(row, m2.cols());
        for(int i = 0; i < row; i++){
            for(int j = 0; j < m2.cols(); j++){
                double wynik = 0;
                for(int k = 0; k < m2.rows(); k++){
                    double skladowa = matrix[i][k] * m2.matrix[k][j];
                    wynik += skladowa;
            }
            matrix_mul.matrix[i][j] = wynik;
        }
        }
        return matrix_mul;
    }else exit(1);  
}

/*zapisywanie do pliku*/

 void Matrix::store(string filename, string path){
     ofstream file;
     path += "/" + filename;
     file.open(path);
     if(file.is_open()){
         file<<row<<" "<<columns<<endl;
         for(int i = 0; i < row; i++){
             for(int j = 0; j < columns; j++){
                 file<<matrix[i][j]<<" ";
             }
             file<<"\n";
         }
         file.close();
     }else cout<<"Blad. Plik nie zostal otwarty"<<endl;
 }

 /*destruktor*/

 Matrix::~Matrix(){
 }