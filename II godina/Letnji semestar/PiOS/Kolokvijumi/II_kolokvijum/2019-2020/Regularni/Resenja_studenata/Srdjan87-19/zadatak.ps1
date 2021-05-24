
# Promena datuma kreiranja: (Get-ChildItem path\to\file.extension).CreationTime = (Get-Date).addYears(-1)

# Set-Location ?
# (Get-ChildItem ".\test\1-god(move).txt").CreationTime = (Get-Date).addYears(-1)
# (Get-ChildItem ".\test\1-year(delete).txt").CreationTime = (Get-Date).addYears(-1)
# (Get-ChildItem ".\test\2-god(move).txt").CreationTime = (Get-Date).addYears(-2)
# (Get-ChildItem ".\test\3-god(move).txt").CreationTime = (Get-Date).addYears(-1)
# (Get-ChildItem ".\test\juce(nothing).txt").CreationTime = (Get-Date).addDays(-1)

### FUNCTIONS


function obrada($fajl, $str, $dest) {
    $razlika = (Get-Date) - $fajl.CreationTime
    
    #echo "Dobijeno: "
    #echo $fajl.FullName

    if( $razlika.TotalDays -ge 365 ) {
        if ( $fajl.Name.Contains($str) ) {
            Move-Item $fajl.FullName -Destination $dest  # stariji od godinu dana i u imenu sadrži zadati string
        }
        else {
            Remove-Item $fajl.FullName                   # stariji od godinu dana i u imenu ne sadrži zadati string
        }
    }
    else {
        if( $fajl.Name.Contains($str) ) {
            Copy-Item $fajl.FullName -Destination $dest  # nije stariji od godinu dana i u imenu sadrži zadati string
        }
    }
}

###

if( $args.Count -ne 3 ) {
    Write-Output "Potrebno je proslediti 3 parametra"
    exit 1
}

$dir = $args[0]
$str = $args[1]
$naziv_pd = $args[2]

if( !(Test-Path $dir -PathType Container) ) {
    Write-Output "Prvi parametar predstavlja nevalidnu putanju"
    exit 2
}

if( (Convert-Path $dir) -eq (Get-Location).ToString() ) {
    Write-Output "Prvi parametar ne moze biti trenutna putanja"
    exit 3
}

if( Test-Path $dir\$naziv_pd -PathType Container ) {
    Write-Output "Folder $naziv_pd vec postoji na putanji: $dir"
    exit 4
}
else {
    New-Item -ItemType Directory -Name $naziv_pd -Path $dir | Out-Null
}


$fajlovi = Get-ChildItem $dir -Recurse -File 

Write-Output $fajlovi | foreach {
    if( $_.BaseName.Contains($str) ) {

        Write-Output ""
        Write-Output $_.FullName
        $akcija = Read-Host -Prompt "Izaberi akciju: Copy, Move, Delete, None"

        if( $akcija -eq "Copy" ) {
            Copy-Item $_.FullName -Destination .
        }
        elseif( $akcija -eq "Move" ) {
            Move-Item $_.FullName -Destination .
        }
        elseif( $akcija -eq "Delete" ) {
            Remove-Item $_.FullName
        }
        else {
            obrada $_ $str $dir\$naziv_pd
        }
    }
    else {
        obrada $_ $str $dir\$naziv_pd
    }
}   
