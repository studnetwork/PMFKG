 
# Dodavanje bootstrap-a

U `styles.css` dodati sledeci kod:
```
@import "https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"
```

# Fajl sa konstantama okruzenja

U `src/app` napraviti folder `environments` i u njemu fajl `environment.ts`.

U ovom fajlu je potrebno napraviti konstantak objekat koji ce sadrzati konstante:
```
export const environment = {
    konst1: "value1",
    konst2: "value2",
    konst3: "value3"
};
```

# Prihvatanje stringa iz response body-a

Za to je potrebno koristiti treci argument metoda klase `HttpClient`.

Potpis ovih izgleda (uprosceno) ovako: `requestMethod(url, body, options)`.

`options` je u stvari objekat koji ima odredjena polja u kojima se definisu te opcije.

Polje koje je bitno u ovom slucaju je polje `responseType`.

Moguce vrednosti ovog polja su: `json`, `text`, `blob`, `arraybuffer`

Nama je potreban `text`:
```
return this.http.post(
    this.registerUrl, {
        email: email, 
        name: name, 
        password: password
    }, { 
        responseType: 'text'
    }
);
```


# Rutiranje u angularu

## Opste

Angular koristi strategiju match-ovanja po kojoj se match-uje prvi patern koji
zadovoljava data ruta.

Zbog toga se genericki paterni stavljaju na kraj liste, slicno kao kod try/catch
bloka i exception-a.

Prvo idu specificni, pa onda manje specificni paterni.

Postupak:
1. Zapocinje se sa staticnim rutama.
2. Nakon njih rute koje su prazne (match-uju default rutu).
3. Na kraju liste nalaze se rute koje sadrze wildcard karakter. To su rute koje
   match-uju svaki URL.

## Dodatno

Umesto `navigate()` moguce je koristiti i:
```
this.router.navigateByUrl("/login");
```

# Primer transformisanja jednog return tipa u drugi
```
uradiNesto(param1: Type1, param2: Type2): Observable<Type3> {
    let res = this.http.post<Type4>(this.url, {param1: param1, param2: param2});
    
    return res.pipe( 
    
      map( type4Instance => {      
        let type3Instance = Type3.covert(type4Instance);
        return type3Instance;
      })
      
    );
    
  }
```

Response type je tipa `Type4`. Pozivalac ocekuje `Observable` tipa `Type3`.

Rezultat `post` metode je `Observable<Type4>` koji ce biti pajpovan u `map`.

Map ce mapirati taj objekat na neki nacin i onda vratiti instancu ocekivanog tipa,
tj. instancu tipa `Type3`.


# Kako omoguciti injecting JwtModlue-a ukoliko se jwt cuva u cookie-u

Potrebno je da se iskoristi `.forRoot` i da se u njemu definise kako ce se 
doci do jwt-a. Obicno se jwt cuva u localstorage-u, ali resenje u ovom slucaju
izgleda ovako:
```
// dodati u:
//     app.module.ts > imports

JwtModule.forRoot({
      config: {
        tokenGetter: (req) => {
            const token = req?.headers?.get("Authorization")?.replace("Bearer ", "");
            if(token == null)
              return "";

            return token;
        }
      }
    })
  ],
```

Moguce je da `null` check nije potreban jer izgleda da je i `null` jedan od dozvoljenih
return tipova.
