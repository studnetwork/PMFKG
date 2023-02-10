# Uputstvo za korišćenje modula za izradu seminarskog iz predmeta Web1

## Klasa Hash

```python
from server_utils import Hash # import se moze razlikovati

Hash.hash(password) # vraca hash


Hash.compare(password,storedPassword) """ vraca True ako su obicna lozinka i hesovana lozinka iste """
```

## Klasa Session

```python
# ucitavanje neophodnih modula

import os
from http.cookies import SimpleCookie

# ucitavanje klase Session
from server_utils import Session

cookie=SimpleCookie(os.environ['HTTP_COOKIE']) # uzima sve cookie-je
session=Session(cookie) # isto kao session_start() u PHP
session['aaa'] # uzimanje vrednosti ( vrednost je string ili None )
session['aaa']="bbb" # dodela vrednosti ( dodeljuje se string ili None )
```
**Ako je u pitanju login ili logout stranica tada je obavezno prilikom stampanja hedera, stampati i cookie**
```python
print('Content-Type:text/html')
print(cookie.output())
print()
print("""
<!DOCTYPE html>
<html>
...
</html>
""")
```
## redirect_to_page funkcija

Izmeniti funkciju prema svojim potrebama.

## Uzimanje objekta konekcije
```python
from server_utils import SingletonConnection

connection=SingletonConnection().connection
```
