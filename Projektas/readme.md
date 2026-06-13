# Automobilių valdymo sistema

## Projekto tikslas

Konsolinė C++ programa, skirta automobilių duomenims saugoti ir valdyti.

## Tema

Programa leidžia vartotojui pridėti, peržiūrėti, redaguoti ir ištrinti automobilių įrašus. Duomenys saugomi tekstiniame faile.

## Funkcionalumas

- Visų automobilių sąrašo peržiūra
- Automobilio paieška pagal ID
- Naujo automobilio pridėjimas
- Esamo automobilio redagavimas
- Automobilio ištrynimas
- Sąrašo rikiavimas pagal kainą, metus arba ridą
- Paieška pagal markę, metų arba kainos intervalą

## Failai

- `main.cpp` – programos kodas
- `cars.txt` – duomenų failas

### Duomenų failo formatas

Kiekviena eilutė yra vienas automobilis, laukai atskirti kabliataškiu:

```
ID;Markė;Modelis;Metai;Kaina;Rida
1;Toyota;Corolla;2018;9500.00;112000
```

## Paleidimas

Kompiliavimas su g++:

```bash
g++ -o cars main.cpp
./cars
```

Naudojant CLion – atidaryti projektą ir paleisti per IDE. Svarbu: `cars.txt` failas turi būti `cmake-build-debug` aplanke, nes ten CLion patalpina sukompiliuotą programą ir iš ten ją paleidžia.

## Papildomos funkcijos

1. **Rikiavimas** – rikiuoja sąrašą pagal kainą, metus arba ridą
2. **Paieška** – ieško automobilių pagal markę, metų arba kainos intervalą