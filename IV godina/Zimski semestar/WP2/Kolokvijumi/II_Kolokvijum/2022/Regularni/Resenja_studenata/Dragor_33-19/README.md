# struktura.png
- Zeleno: Novi fajlovi
- Zuto: Izmenjeni fajlovi

# package.json (npm run)
Pomocu komande `npm run <precica>` moze se pokrenuti neka druga komanda definisana u `package.json` fajlu.
U ovom projektu dodate su sledece precice (skripte):
```json
"scripts": {
    ...
    "gc": "ng g c --skip-tests --style none -t --flat",
    "gs": "ng g s --skip-tests",
    "gg": "ng g g --skip-tests"
}
```
Primer koriscenja:
```
npm run gc ui/comp/navbar
npm run gs srv/auth
npm run gg grd/logged-in
```

komande:
- `ng g c` (`ng generate component`)
- `ng g s` (`ng generate service`)
- `ng g g` (`ng generate guard`)

opcije:
- `--skip-tests` : ne kreira `.spec.ts` fajl (sluzi za testiranje)
- `--style none` : ne kreira `.css` fajl za komponentu
- `-t` : ne kreira `.html` fajl za komponentu
- `--flat` : ne kreira poseban folder za falove komponente
