@echo off
setlocal

for /r .\testdata %%f in (*) do (
	for /f "usebackq delims=" %%l in ("%%f") do (
		for %%w in (%%l) do (
			set /a count[%%w]=count[%%w]+1
		)
	)
)

set count