# Pisanje formula u MathJax-supported formatu

* `^{\prime}` se koristi umesto `'`
  * primer: `m'_{i}` -> `m_{i}^{\prime}`
* za vise liniju unutar math bloka, koristiti:
  ```
  $$
  \begin{gather*}
  ... \\
  ... \\
  ...
  \end{gather*}
  $$
  ```
  `*` iskljucuje numbering sa desne strane (neki engine-i ga renderuju)
* math blok se ne renderuje ukoliko iznad i ispod `$$` ne postoji prazna linija