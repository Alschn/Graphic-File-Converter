## Skład zespołu (gr. 208):
* Gustaw Daczkowski
* Wojciech Nowicki
* Adam Lisichin

Wybrane środowisko to Visual Studio 2019.

### Temat projektu:
Konwersja .bmp <-> pliki nagłowkowe pamieci (statyczna).
Wyświetlanie obrazów w formie tekstowej (ASCII).
Optymalizacja pamięci pod względem przechowywanego obrazu.


### Wstępna funkcjonalność:
* Wczytywanie obrazu do pamięci z pliku .bmp (24bpp).
* Obracanie obrazu o kąt całkowitej wielokrotności 90 stopni.
* Odbijanie obrazu względem przekątnej oraz względem środka w pionie jak i w poziomie.
* Dynamiczny CLI

### Uruchamianie programu
* Program będzie uruchamiany z wiersza poleceń poprzez podanie odpowiednich argumentów
* W przypadku niepodania argumentów program będzie działał w trybie pilotażowym (wprowadzanie opcji po kolei)
* Program będzie wyświetlał dynamicznie formułowaną pomoc.


### Literatura

 [Struktura pliku BMP](http://www.ue.eti.pg.gda.pl/fpgalab/zadania.spartan3/zad_vga_struktura_pliku_bmp_en.html)


#### Aktualny podział pracy:
* Klasa `UserInterface` odpowiedzialna za dynamiczny CLI - Wojciech Nowicki
* Klasy `Parameter` oraz dziedziczące z nich - odpowiadają za opcjonalne parametry CLI - Wojciech Nowicki
* Klasa `Image` odpowiadająca za przechowywanie zdjęcia w pamięci jak i zamianę go na tekst - Gustaw Daczkowski
* Klasa `Converter` klasa główna odpowiedzialna za konwersję, z wirtualnymi metodami - Gustaw Daczkowski
* Klasa `Rotate` dziedzicząca z `Converter` w celu konwersji zdjęcia - obrotu - Adam Lisichin
* Klasa `Reflection` dziedzicząca z `Converter` w celu konwersji - odbicia lustrzanego - Adam Lisichin
* Klasa `Utils`- bardzo mała, znajdują się w niej statyczne metody do obsługi operacji bitowych oraz bajtowych - Gustaw Daczkowski


#### Testy jednostkowe:
* Do testowania został użyty `MicrosoftCppUnitTestFramework`. Wszystkie testy znajdują się w oddzielnym projekcie `tests`.
* Klasy `Image`, `Reflection`, `Rotation` oraz `UserInterface` są testowane jednostkowo.

#### Aktualna funkcjonalność programu:
* CLI reaguje na komendę --help i wyświetla pomoc dla użytkownika, przy każdej źle wpisanej komendzie  
również wyśtwietla pomoc, CLI jest gotowy do rejestracji kolejnych funckjonalności programu.
* CLI obsługuje dwie komendy konwersji zdjęć:
    1. **Obrót o zadany kąt:** converter rotation kąt "scieżka wejściowa" ["scieżka wyjściowa"] [-d]
    2. **Odbicie lustrzane:** converter reflection tryb "scieżka wejściowa" ["ścieżka wyjściowa"] [-d]
* Klasa `Image` obsługuje wczytywanie obrazu z pamięci, natomiast owa funkcjonalność nie jest zaimplementowana w CLI.
Aby przetestować ten tryb należy odkomentować odpowiednie linijki w `main.cpp` - jest to zaznaczone w komentarzu na początku funkcji `main()`.
* Ponadto klasa `Image` ma zaimplementowane operatory `<<` oraz `>>` służące do wypisywania treści zdjęcia oraz ładowania treści do zdjęcia z pliku (bajty).
* W obecnym momencie tryb wypisywania na ekranie zdjęcia realizowany przez klasę `Image` uwzględnia wypisywanie 1px - 1litera. 
Wypisywane są litery R|G|B w zależności od tego, który z kolorów w danym pikselu jest najbardziej dominujący.



### Przykładowe użycie programu:
* `converter rotation 90 "../sample_bmps/10x10.bmp" -d` - obrót zdjęcia 10x10.bmp o 90 stopni w prawo.
Podanie opcjonalnego parametru `-d` powoduje wyświetlenie zdjęcia na ekranie konsoli.
* `converter reflection 2 "../sample_bmps/10x10.bmp" "../sample_bmps/output.bmp"` odbicie symetryczne względem prostej y=x i zapis do pliku output.bmp.

*Szczegółowe objaśnienia komend znajdują się w #11.
*Szczegółowe objaśnienia funkcjonalności klasy `Image` znajduje się w #10.
*Szczegółowe objaśnienia trybów konwersji znajdują się w #9.



