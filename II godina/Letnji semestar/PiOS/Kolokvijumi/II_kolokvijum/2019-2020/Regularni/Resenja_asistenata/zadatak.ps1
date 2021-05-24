if($args.Length -ne 3){
    echo "Nema tri argumenta"
    exit 1
}

$dir1 = $args[0]
$fajl = $args[1]
$dir2 = $args[2]

if(!(Test-Path $dir1 -PathType Container)){
    echo "Argument 1 ne postoji"
    exit 1
}

if((Test-Path $dir1\$dir2 -PathType Container)){
    echo "Argument 3 postoji"
    exit 1
}

mkdir $dir1\$dir2 > $null


dir $dir1 -Recurse -File | foreach {
    echo $_.Name
    $ind = 0
    if($_.Name.Contains($fajl)){
        echo $_

        $akcija = Read-Host
        if($akcija -eq "Copy"){
            #echo "COPY"
            $ind = 1
            Copy-Item $_.FullName .
        }
        elseif($akcija -eq "Move"){
            Move-Item $_.FullName .
            $ind = 1
        }
        elseif($akcija -eq "Delete"){
            #echo "DELETE"
            $ind = 1
            Remove-Item $_.FullName
        }
    }
    else{
        if(((Get-Date) - $_.CreationTime).totaldays -gt 365){
            Remove-Item $_.FullName
            $ind = 1
        }
    }

    if($ind -eq 0){
        if(((Get-Date) - $_.CreationTime).totaldays -lt 365){
            Copy-Item $_.FullName $dir1\$dir2
        }
        else{
            Move-Item $_.FullName $dir1\$dir2
        }
    }
}
