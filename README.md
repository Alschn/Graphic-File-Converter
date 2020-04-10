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
* Program będzie wyświetlał dynamicznie formułowaną pomoc


### Literatura

 [Struktura pliku BMP](http://www.ue.eti.pg.gda.pl/fpgalab/zadania.spartan3/zad_vga_struktura_pliku_bmp_en.html)


#### Aktualny podział pracy:
* Klasa `Image` odpowiadająca za przechowywanie zdjęcia w pamięci jak i zamianę go na tekst - Gustaw Daczkowski
* Klasa `UserInterface` odpowiedzialna za dynamiczny CLI - Wojciech Nowicki
* Klasa `Rotate` dziedzicząca z `Converter` w celu konwersji zdjęcia - obrotu - Adam Lisichin.  
* Klasa `Reflection` dziedzicząca z `Converter` w celu konwersji - odbicia lustrzanego - Adam Lisichin/


#### Testy jednostkowe:
* Do testowania został użyty `MicrosoftCppUnitTestFramework`. Wszystkie testy znajdują się w oddzielnym projekcie `tests`.
* Każda z wymienionych wyżej klas jest testowana jednostkowo. 

#### Aktualna funkcjonalnośc programu:
* CLI reaguje na komendę --help i wyświetla pomoc dla użytkownika, przy każdej źle wpisanej komendzie  
również wyśtwietla pomoc, CLI jest gotowy do rejestracji kolejnych funckjonalności programu

