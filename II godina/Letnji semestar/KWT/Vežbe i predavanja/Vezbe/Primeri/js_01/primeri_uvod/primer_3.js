let c = 0
function count(element) {
    element.innerHTML += '<br><em>ADDED TEKST: ' + c + '</em>'
    c++
}

let paragraf = document.getElementById('p1')
paragraf.innerHTML = '<strong>CLICK THIS PARAGRAPH!</strong>'

function onKeyDown() {
    console.log('On Key Down')
    count(paragraf)
}