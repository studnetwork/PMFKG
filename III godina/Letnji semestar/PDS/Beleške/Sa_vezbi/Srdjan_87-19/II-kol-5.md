JSTL - JSP Standard Tag Library

Importovanje tagova iz biblioteke jstl:
```
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %> 
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %> 
```

Ispis teksta pomocu jstl umesto preko tagova:
```
<c:out value="${'ispis'}" />
```


Skladistenje sadrzaja neke html stranice u promenljivu:
```
<c:import var="data" url="https://www.javapoint.com" />

<!-- ispis zadrzaja var -->
<c:out value="${data}" />
```


Setovanje ili brisanje vrednosti u neku promenljivu:
```
<!-- setovanje -->
<c:set var="income" scope="session" value="${4000 * 4}" /> 

<c:out value="${income}" /> 

<!-- brisanje -->
<c:remove var="income" /> 
```


Nesto slicno try/catch-u:
```
<c:catch var="nazivVarUkojojCeBitiSacuvanException">
    <% 
        int broj = 5 / 0;
    %>
</c:catch>

<c:if test="${nazivVarUkojojCeBitiSacuvanException != null}">
    <p>Tip greske je: ${nazivVarUkojojCeBitiSacuvanException}</p><br>
    <p>Poruka: ${nazivVarUkojojCeBitiSacuvanException.message}</p>
<c:if
```

`nazivVarUkojojCeBitiSacuvanException` ce biti `null` ukoliko ne dodje do izuzetka


Mogu se koristiti i poredjenja kao i drugi izrazi:
```
<c:if test="${ 10 > 5 }">

<c:out value="${ (10>5) ? "jeste" : "nije" }">
```


Nesto slicno switch-u:
```
<c:choose>
    <c:when test="${zarada > 50000}">
        Prihodi su mali
    </c:when>
    <c:when test="${zarada > 100000}">
        Prihodi su veliki
    </c:when>
    <c:otherwise>
        Prihodi su osrednji
    </c:otherwise>
</c:choose>
```

Petlje:
```
<c:forEach var="i" begin="0" end="5">
    <p>Indeks: ${i}</p>
</c:forEach>
```


```
<c:forTokens items="Programiranje-slozenih-softverskih-sistema" delims="-" var="rec">
    ${rec}
</c:forTokens>
```

```
<c:url value="/index.jsp" var="completeUrl">
    <c:param name="id" value="255"/>
    <c:param name="username" value="Petar"/>
</c:url>

${completeUrl}
```


```
<c:set var="amount" value="${123.456}" /> 
<fmt:parseNumber var="j" type="number" value="${amount}"/>

${j}

<fmt:parseNumber var="round_j" integerOnly="true" type="number" value="${amount}"/>
${round_j}
```

Datumi:
```
<c:set var="datum" value="<%= new java.util.Date()" %>" />   
<fmt:formatDate value="${datum}" type="both" timeStyle="long" dateStyle="long" />

<c:forEach var="zone" items="<%= TimeZone.getAvailableIDs() %>"
    <fmt:timeZone value="${zone}>
        <fmt:formatDate value="${datum}" timezone="${zone}" type="both" />
        <bt>
    </fmt:timeZone>
</c:forEach>
```

`type="both"` oznacava da treba ukljuciti i vreme i datum


Parsiranje stringa u datum:
```
<c:set var="datum" value="12-08-2023" />
<fmt:parseDate var="parseDate" value="${datum}" pattern="dd-MM-yyyy" />
```

---

Rad sa brojevima:
```
<c:set var="amount" value="1234.567" />

<!-- ovo se odnosi na to da li ce se odvajati svake 3 cifre: 1000000 vs 1.000.000 -->
<fmt:formatNumber value="${amount}" type="number" groupingUsed="false" /> 
<br>

<!-- koliko ce se ispisati maksimalno cifara levo od zareza (1234 => 234) -->
<fmt:formatNumber value="${amount}" type="number" maxIntegerDigits="3" />
<br>

<!-- koliko ce se ispisati maksimalno cifara desno od zareza, tj. decimala -->
<fmt:formatNumber value="${amount}" type="number" maxFractionDigits="3" />
<br>

<fmt:formatNumber value="${amount}" type="percentage" />
<br>

<!-- custom format; # predstavlja jednu cifru ili mesto -->
<fmt:formatNumber value="${amount}" type="number" pattern="###.## RSD" />
<br>
```

---

Preuzimanje vrednosti iz tag-a:
```
<% 
    String name="PSSS";
%>

<c:set var="naziv_predmeta"><%= name %></c:set>

Ime je: <c:out value="${naziv_predmeta}" />



<%
    String imeIzTaga = (String) pageContext.getAttribute("naziv_predmeta");
    // ...
%>
```

Da bismo pristupili vrednosti promenljive koja je setovana sa `session.setAttribute`
potrebno je da ona ima definisan scope `session`


