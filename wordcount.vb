Imports System.Text.RegularExpressions

Module WordCount

    Dim records As New Dictionary(Of String, Integer)

    Sub CountInFile(ByRef file As IO.FileInfo)
        Dim content = IO.File.ReadAllText(file.FullName)
        Dim words = Regex.Split(content, "\s+")
        For Each word In words
            If records.ContainsKey(word) Then
                records.Item(word) += 1
            Else
                records.Item(word) = 1
            End If
        Next
    End Sub

    Sub WalkDir(ByRef directory As IO.DirectoryInfo)
        For Each file In directory.GetFiles
            CountInFile(file)
        Next
        For Each subDir In directory.GetDirectories
            WalkDir(subDir)
        Next
    End Sub

    Sub Main()
        WalkDir(New IO.DirectoryInfo("./testdata"))
        For Each kv As KeyValuePair(Of String, Integer) In records
            Console.WriteLine($"{kv.Key} {kv.Value}")
        Next
    End Sub

End Module
