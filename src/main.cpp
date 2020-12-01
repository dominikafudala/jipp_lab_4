#include <Matrix/matrix.hpp>

using namespace std;


int main(){

    while(1){
        cout<<"1 - stworz macierz kwadratowa(zaprezentowane metody set, cols, rows, print, add, store)"<<endl;
        cout<<"2 - stworz macierz niekwadratowa(zaprezentowane metody get, subtract, multiply, print) "<<endl;
        cout<<"3 - wczytaj macierz z pliku"<<endl;
        cout<<"4 - zakoncz program"<<endl;

        int choice = 0;
        cin >> choice;

        switch(choice){
            case 1: {
                Matrix macierz1(4, 6);
                macierz1.print();
                cout<<"Liczba wierszy i kolumn"<<endl;
                int cols_1 = macierz1.cols();
                int rows_1 = macierz1.rows();
                cout<<"wiersze = "<<rows_1<<" kolumny = "<<cols_1<<endl;
                cout<<"Ustawianie wartosci macierzy: "<<endl;
                for(int i = 0; i < macierz1.rows(); i++){
                    for(int j = 0; j < macierz1.cols(); j++){
                         macierz1.set(i, j, 1);
                     }
                }
                macierz1.print();
                cout<<"Dodawanie"<<endl;
                cout<<"Tworze druga macierz"<<endl;
                Matrix m2_sum(4, 6);
                m2_sum.set(1, 1, 3.2);
                m2_sum.set(3, 5, 2);
                m2_sum.set(2, 2, 7);
                m2_sum.print();
                Matrix m_sum_wynik = macierz1.add(m2_sum);
                cout<<"Wynik dodawania: "<<endl;
                m_sum_wynik.print();
                cout<<"Czy chcesz zapisać wynik do pliku? y/n"<<endl;
                char inp;
                cin>>inp;
                if('y' == inp){
                    cout<<"Plik zapisany w biezacym katalogu pod nazwa msumfile"<<endl;
                    m_sum_wynik.store("msumfile", "./");
                }
                break;
                }
            case 2: {
                Matrix kwadratowa(4);
                kwadratowa.print();
                kwadratowa.set(1, 3, 2.2);
                kwadratowa.print();
                cout<<"Pobieranie elementu 1x3"<<endl;
                double element = kwadratowa.get(1, 3);
                cout<<"Element ten to: "<<element<<endl;
                cout<<"Tworzymy macierz która nam posłuży do odejmowania i mnożenia: "<<endl;
                Matrix dzialania(4);
                dzialania.set(0,0,3);
                dzialania.set(1,3,2);
                dzialania.set(3, 3, 2.2);
                dzialania.print();
                cout<<"Wynik odejmowania: "<<endl;
                kwadratowa.subtract(dzialania).print();
                cout<<"Wynik mnozenia: "<<endl;
                kwadratowa.multiply(dzialania).print();
                break;
                }
            case 3: {
                cout<<"Wczytanie macierzy z pliku msumfile z katalogu biezacego"<<endl;
                Matrix zpliku("./msumfile");
                zpliku.print();
                break;
                }
            case 4: return 0;
            default: {
                cout<<"Brak opcji."<<endl;
                break;
            } 


        }

    }
}
