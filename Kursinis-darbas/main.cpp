#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace chrono;

long long palyginimų_sk = 0;
long long sukeitimų_sk = 0;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int raktas = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > raktas) {
            palyginimų_sk++;
            arr[j + 1] = arr[j];
            sukeitimų_sk++;
            j--;
        }
        if (j >= 0) palyginimų_sk++;
        arr[j + 1] = raktas;
    }
}

void merge(vector<int>& arr, int kair, int vid, int des) {
    int n1 = vid - kair + 1;
    int n2 = des - vid;

    vector<int> K(n1), D(n2);
    for (int i = 0; i < n1; i++) K[i] = arr[kair + i];
    for (int i = 0; i < n2; i++) D[i] = arr[vid + 1 + i];

    int i = 0, j = 0, k = kair;
    while (i < n1 && j < n2) {
        palyginimų_sk++;
        if (K[i] <= D[j]) {
            arr[k++] = K[i++];
        } else {
            arr[k++] = D[j++];
            sukeitimų_sk++;
        }
    }
    while (i < n1) arr[k++] = K[i++];
    while (j < n2) arr[k++] = D[j++];
}

void mergeSort(vector<int>& arr, int kair, int des) {
    if (kair < des) {
        int vid = kair + (des - kair) / 2;
        mergeSort(arr, kair, vid);
        mergeSort(arr, vid + 1, des);
        merge(arr, kair, vid, des);
    }
}

vector<int> generuotiAtsitiktinius(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = rand() % 100000;
    return arr;
}

vector<int> generuotiSurikiuotus(int n) {
    vector<int> arr(n);
    iota(arr.begin(), arr.end(), 1);
    return arr;
}

vector<int> generuotiAtvirksciai(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = n - i;
    return arr;
}

void testuoti(const string& pavadinimas, vector<int> duomenys, bool mergeFlag) {
    const int KARTAI = 5;
    long long laiko_suma = 0;
    long long palyginimai_suma = 0;
    long long sukeitimai_suma = 0;

    for (int k = 0; k < KARTAI; k++) {
        vector<int> kopija = duomenys;
        palyginimų_sk = 0;
        sukeitimų_sk = 0;

        auto pradzia = high_resolution_clock::now();
        if (mergeFlag)
            mergeSort(kopija, 0, kopija.size() - 1);
        else
            insertionSort(kopija);
        auto pabaiga = high_resolution_clock::now();

        laiko_suma += duration_cast<microseconds>(pabaiga - pradzia).count();
        palyginimai_suma += palyginimų_sk;
        sukeitimai_suma += sukeitimų_sk;
    }

    cout << pavadinimas
         << " | Laikas: " << laiko_suma / KARTAI << " mks"
         << " | Palyginimai: " << palyginimai_suma / KARTAI
         << " | Sukeitimai: " << sukeitimai_suma / KARTAI
         << endl;
}

int main() {
    srand(42);

    vector<int> dydžiai = {5000, 10000, 50000};

    for (int n : dydžiai) {
        cout << "\n====== n = " << n << " ======" << endl;

        vector<int> atsitiktiniai = generuotiAtsitiktinius(n);
        vector<int> surikiuoti    = generuotiSurikiuotus(n);
        vector<int> atvirksciai   = generuotiAtvirksciai(n);

        cout << "-- Nesurikiuoti --" << endl;
        testuoti("InsertionSort", atsitiktiniai, false);
        testuoti("MergeSort    ", atsitiktiniai, true);

        cout << "-- Jau surikiuoti --" << endl;
        testuoti("InsertionSort", surikiuoti, false);
        testuoti("MergeSort    ", surikiuoti, true);

        cout << "-- Atvirksciai surikiuoti --" << endl;
        testuoti("InsertionSort", atvirksciai, false);
        testuoti("MergeSort    ", atvirksciai, true);
    }

    return 0;
}