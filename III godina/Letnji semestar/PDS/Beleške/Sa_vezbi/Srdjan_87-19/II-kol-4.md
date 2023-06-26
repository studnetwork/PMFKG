# JSF

xhtml - Extended HTML 


> Cilj kod ovih tehnologija je da se na osnovu forme automatski kreira instanca klase

Iznad Java Bean-a stavljamo anotaciju `@ManagedBean` koja se nalazi u paketu
`javax.faces.bean` (postoji i neka druga iz drugog paketa, ali ne treba nam ona)


To omogucava koriscenje klase u `.xhtml` fajlovima, a i pored toga imamo mogucnost
fleksibilnijeg rada sa tim bean-ovima (navodjenje drugacijeg imena sa 
`@ManagedBean(name="nekoIme")`, ...)


Pored te anotacije dodaje se i `@RequestScope` kojom se oznacava da instanca vazi 
dok traje obrada datog zahteva.


Kada korisnik ode na `index.jsf` bice mu usluzen `index.xhtml`

---

Jedna od razlika JSF od JSP je to sto tagovi imaju prefiks `h`, npr `<h:head>Heder</h:head>`.

To `h` dolazi iz import-a `<html xmlns="http://www.w3.org/1999/xhtml" xmlns:h="http://xmlns.jcp.org/jsf/html">`.

To nam omogucava da imamo komunikaciju izmedju njih i Jave, tj. da se deo jave nadje u njima.

Ovo je obicno default-ni import. Pored njega potrebno je da rucno uvezemo `core` navodjenjem ns u html tagu:
```
<html ... xmlns:f="http://xmlns.jcp.org/jsf/core">
```



Pisanje forme:
```
<h:form id='form'>
    <table>
        <tr>
            <td>
                <h:outputLabel for='username'>Username:</h:outputLabel>
            </td>
            <td>
                <h:inputText id='username' value='#{imeIzBeanaUAnotacijiManagedBean.name}'></h:inputText>
            </td>
        </tr>
    </table>
</h:form>
```

`<h:inputText value='#{imeIzBeanaUAnotacijiManagedBean.name}'></h:inputText>` moze da se pise krace, bez closing tag-a:
`<h:inputText value='#{imeIzBeanaUAnotacijiManagedBean.name}'/>`


Radio button:
```
<h:selectOneRadio value="#{user.gender}">
    <f:selectItem itemValue="Female" itemLabel="female"/>
    <f:selectItem itemValue="Male" itemLabel="male"/>
</h:selectOneRadio>
```


```
<!-- textarea -->
<h:inputTextarea cols="50" rows="5" value="#{user.address}"/>

<!-- button -->
<h:commandButton value="submit" action="response.xhtml"></h:commandButton>

<h:outputText value="Preuzimanje podataka iz instance bean-a: #{user.name}" />
```


Ako se dogodi da managed bean nije prepoznat, u `faces-config.xml` moze da se
doda u potkartici `ManagedBean`.


## Validacija formi

Validator mora isto da bude managed java bean.

```
<h:form id='form'>
    <h:outputLabel for='name'>Name:</h:outputLabel>
    <h:inputText id='name' value='#{validacija.name}' validatorMessage="Neka poruka">
        <f:validateRegex pattern="^([a-zA-Z]+(.)?[\s]*)$" />
    </h:inputText>
</h:form>
```

Ova validacija se vrsi na serverskoj strani. Da je izvrsena na klijentskoj strani
neko bi mogao da je zaobidje ukoliko bi poslao zahtev direktno na server (backend).


## File Upload

Kada radimo upload fajla koristimo tip `Part` iz `javax.servlet.http`.
npr. `private Part fajl;`


Klasa koja vrsi upload mora da ima i metodu pomocu koje cuvamo taj fajl.
```Java
public void save() {
    try (InputStream input = file.getInputStream()) {
        // putanja mora da bude escaped
        Files.copy(input, new File("putanja//do//dir//na//fs", file.getSubmittedFileName()).toPath()); 
    } catch(Exception e) {
        e.printStackTrace();
    }
}
```

U xhtml:
```
<h:form id="form" enctype="multipart/form-data">
    <h:outputLabel for='input_file'>Izaberi fajl</h:outputLabel>
    <h:inputFile id='input_file' value='#{uploadFile.file}'>
        <f:ajax listener="#{uploadFile.save}" />
    </h:inputFile >
</h:form>
```

> `listener` osluskuje i ceka da se fajl upload-a. Kada se upload-a tada vrsi asinhroni poziv ka serveru 


Upload preko built-in eclipse browser-a moze dosta da potraje pa ne se preporucuje da se to testira preko njega.

## Hesiranje sifre

```Java
public static String sha1(Strint input) {
    String sha1 = null;
    MessageDigest digest;
    try {
        digest = MessageDigest.getInstance("SHA-1");
        digest.reset();
        digest.update(input.getBytes("utf8"));
        sha1 = String.format("%040x", new BigInteger(1, digest.digest()));
    } catch (Exception e) {
        e.printStackTrace
    }
    
    return sha1;
}  
```
