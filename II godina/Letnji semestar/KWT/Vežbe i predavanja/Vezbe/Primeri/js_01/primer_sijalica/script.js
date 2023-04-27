/* --- Kalkulator --- */

function add()
{
    let a = document.getElementById('sabirak-1').value
    let b = document.getElementById('sabirak-2').value

    a = Number(a)
    b = Number(b)

    document.getElementById('zbir').innerHTML = a + b
}

/* --- Telefon --- */

function setImg(select)
{
    console.log('Set Image')
    let img = document.getElementById('telefon')
    img.src = 'images/' + select.value
}

/* --- Sijalica --- */

let isOn = false

/* Verzija 1 */
function toggleBulb(bulb)
{
    isOn = !isOn
    
    if(isOn == true)
        bulb.src = 'images/pic_bulbon.gif'
    else
        bulb.src = 'images/pic_bulboff.gif'
}












/* ------------ Testiranje ------------ */

/* Verzija 2 */
/*function toggleBulb(bulb)
{
    isOn = !isOn    
    bulb.src = isOn ? 'images/pic_bulbon.gif' : 'images/pic_bulboff.gif'
}*/

/* Verzija 3 */
/*function toggleBulb(bulb)
{
    isOn = !isOn
    bulb.src = `images/pic_bulb${ isOn ? 'on' : 'off' }.gif`
}*/

/* Verzije X */
let toggleBulbX = (bulb) =>  bulb.src = `images/pic_bulbo${ (isOn = !isOn) ? 'n' : 'ff' }.gif`

function addX()
{
    let get = (x,p=true) => p ? Number(document.getElementById(`sabirak_${x}`).value) : document.getElementById(x)
    get('zbir',false).innerHTML = get('1') + get('2')
}