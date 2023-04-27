let page = document.getElementById('page')

for(let i = 1; i <= 100; i++) 
{
    page.innerHTML += `${i}. red teksta <br>` // template literal
    
    if(i % 2 == 0) 
        page.innerHTML += '<hr>'
}