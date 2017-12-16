[![Build Status](https://travis-ci.org/ovan-iu8/HW_Explorer_04.svg?branch=master)](https://travis-ci.org/ovan-iu8/HW_Explorer_04) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](/LICENSE)
## Проект Explorer (IV этап)

### Соответствие порядкового номера и комбинации:
- Порядковый номер: **20**
- Двоичное представление: **1 0 1 0 0**
- Комбинация: **0, 0, 1, 1**


## Задание
- [X] Добавить обработку регулярных выражений формата BRE в наименовании путей.
- [X] Подключить библиотеку **Boost.Program_option**.
- [X] Подключить библиотеку **Boost.Regex**.


## Пример
Для комбинации **1, 0, 1, 0**
```
$ ./explorer -r f*.dat 
path:	 /home/user/file.dat
size:	 2258 Kb
date:	 10/17/2017 8:43
```
