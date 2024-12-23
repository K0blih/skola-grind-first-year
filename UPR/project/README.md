
# SPACE INVADERS

## Jak projekt zkompilovat

### 1. Vytvoření složky pro sestavení projektu

```bash
mkdir build
cd build
```

### 2. Použití CMake k sestavení Makefile

```bash
cmake ..
```

### 3. Přeložení projektu

```bash
make
```

### 4. Spuštění hry

```bash
./project
```

---

## Ovládání

- `<`  - pohyb doleva  
- `>`  - pohyb doprava  
- `↑`  - vystřelit  
- `SPACE` - vystřelit  
- `ESC` - ukončit hru  

---

## Poznámky

- Spodní mimozemšťani +1, střední +2, horní +3, vesmírná loď +10-50 bodů
- Maximální skóre je ukládáno do `topScore.txt`.
- Tento projekt vyžaduje knihovnu SDL2.
- Před spuštěním projektu se ujistěte, že máte správně nastavené adresáře a soubory s texturami v CMakeLists.txt (`assets/`, `assets/ARIALBD.TTF`).
