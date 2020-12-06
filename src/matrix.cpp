#include <Matrix/matrix.hpp>

/*exceptions*/
class FileNotOpen : public exception
{
    virtual const char *what() const throw()
    {
        return "Plik nie zostal otwarty";
    }
};

class NoElement : public exception
{
    virtual const char *what() const throw()
    {
        return "Nie ma takiego elementu";
    }
};

class WrongSize : public exception
{
    virtual const char *what() const throw()
    {
        return "Zly rozmiar macierzy";
    }
};

class PrintException : public exception
{
    virtual const char *what() const throw()
    {
        return "Nie mozna wydrukowac";
    }
};

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

Matrix::Matrix(string path) noexcept(false){
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
    }else {
        FileNotOpen filenotopen;
        try
        {
            throw filenotopen;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
}

/*drukowanie macierzy na ekran */

void Matrix::print()noexcept(false){
    if(!matrix.empty()){
        cout<<"Wyswietlanie macierzy "<<row<<"x"<<columns<<endl;
        for(int i = 0; i < row; i++){
            for(int j = 0; j < columns; j++){
                cout<<matrix.at(i).at(j)<<"  ";
            }
            cout<<endl;
    }
    }else
    {
        PrintException noprint;
        try
        {
            throw noprint;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    
    
    
}

/* Pobieranie elem. (n, m)*/

double Matrix::get(int n, int m)noexcept(false){
    // sprawdzanie czy elem. (n, m) istnieje
    if((n < 0 || n >= row) || (m < 0 || m >= columns)){
        NoElement noelem;
        try
        {
            throw noelem;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return matrix[n][m];
}

/*ustawianie wart. elem. (n, m) na val*/

void Matrix::set(int n, int m, double val)noexcept(false){
    if((n < 0 || n >= row) || (m < 0 || m >= columns)){
           NoElement noelem;
        try
        {
            throw noelem;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
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

Matrix Matrix::add(Matrix &m2)noexcept(false){
    if(row == m2.rows() && columns == m2.cols()){
        Matrix matrix_sum(row, columns);
        for(int i = 0; i < row; i++){
            for(int j = 0; j < columns; j++){
                matrix_sum.matrix[i][j] = matrix[i][j] + m2.matrix[i][j];
            }
        }
        return matrix_sum;

    }else{
     WrongSize wrong;
        try
        {
            throw wrong;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        }   
}

Matrix Matrix::subtract(Matrix &m2)noexcept(false){
    if(row == m2.rows() && columns == m2.cols()){
        Matrix matrix_sub(row, columns);
        for(int i = 0; i < row; i++){
            for(int j = 0; j < columns; j++){
                matrix_sub.matrix[i][j] = matrix[i][j] - m2.matrix[i][j];
            }
        }
        return matrix_sub;
    }else {
      WrongSize wrong;
        try
        {
            throw wrong;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        }   
}

Matrix Matrix::multiply(Matrix &m2)noexcept(false){
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
    }else {
      WrongSize wrong;
        try
        {
            throw wrong;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        }  
}

/*zapisywanie do pliku*/

 void Matrix::store(string filename, string path)noexcept(false){
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
     }else {
        FileNotOpen filenotopen;
        try
        {
            throw filenotopen;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
     }
 }

 /*destruktor*/

 Matrix::~Matrix(){
 }