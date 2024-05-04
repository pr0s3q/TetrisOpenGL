# Get all .cpp files recursively
$files = Get-ChildItem -Path "./TetrisOpenGL/src" -Filter "*.cpp" -Recurse

$totalFiles = $files.Count
$currentFileIndex = 1

# Iterate through each file
foreach ($file in $files) {
    # Print progress
    Write-Host "Processing file $currentFileIndex of $totalFiles : $($file.FullName)"

    # Format the file using clang-format
    clang-format.exe -style=file -i $file.FullName

    # Increment the current file index
    $currentFileIndex++
}

# Get all .cpp files recursively
$files = Get-ChildItem -Path "./TetrisOpenGL/include" -Filter "*.h" -Recurse

$totalFiles = $files.Count
$currentFileIndex = 1

# Iterate through each file
foreach ($file in $files) {
    # Print progress
    Write-Host "Processing file $currentFileIndex of $totalFiles : $($file.FullName)"

    # Format the file using clang-format
    clang-format.exe -style=file -i $file.FullName

    # Increment the current file index
    $currentFileIndex++
}