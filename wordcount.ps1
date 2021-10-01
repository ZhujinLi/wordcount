$records = @{}
$files = Get-ChildItem -Path .\testdata -Recurse -File
foreach ($file in $files)
{
    $content = (Get-Content $file.FullName -Raw).ToString()
    $words = $content -split '\s+'
    foreach ($word in $words)
    {
        $records[$word]++
    }
}
Write-Output $records