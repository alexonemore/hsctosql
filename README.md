# __HSCtoSQL__ (HSC to SQLite database converter)

__HSCtoSQL__ is an auxiliary program for converting a database from HSC XML format to SQLite format. 
This program was successfully built using QtCreator with the Qt 5.15.2 and 6.4.1 libraries by the MSVC and MinGW compilers.
To convert, you will need the databases from the HSC program that are not supplied with this program to avoid licensing problems.

## The easiest way to compile and run

1. Download Qt Online Installer from the official website. If you can't download Qt due to internet restrictions, use a VPN or switch to a Linux operating system like Manjaro and install it from the repositories.
2. Install Qt 5.15.2 or Qt 6.4.1.
3. Download __HSCtoSQL__ source code using git (install Git if you don't have it yet).
	```shell
	git clone git@github.com:alexonemore/hsctosql.git
	```
4. Prepare your own 5 database files from the HSC program as described below and put them in `hsctosql/dbsources` directory.
5. Open `CMakeLists.txt` in QtCreator.
6. Build in __Release__ mode. Do not build in Debug mode. A program built in Debug mode is extremely slow.
7. Run it and you get the QSlite database file in one directory above.

## Database files required for the program

1. __Main database__

	```
	1. Open the HSC-Database module
	2. Copy All the Data from Main Database to your Own Database
	3. Save your own database as "hsc_database.xml"
	```

2. __Data references__

	```
	1. Open the "C:\HSC9\Help\32 Data References.pdf" file in MsWord
	2. Remove the header, footer, and text above the table
	3. Select All and Clear All Formatting
	4. Replace All ^t with a space
	5. Replace All ^p with a space
	6. Replace spacespace with a space recursively
	7. Select All, Copy and Paste it in Notepad++
	8. Replace \t" with \t (Extended mode)
	9. Replace "\n with \n  (Extended mode)
	10. Replace \n\n with \n  (Extended mode)
	11. Delete the first empty line if it exists
	12. Delete all characters in the last line, including spaces
	13. Save as "hsc_data_references.txt"
	```

3. __Elements__

	```
	1. Open the HSC-Elements module
	2. Open Database
	3. Save the Table as elements.xlsx
	4. Open elements.xlsx in MsExcel
	5. Ctrl-a, Ctrl-c -> in the new Excel document Paste Special... -> Values
	6. Ctrl-a, Ctrl-c -> in the new list Paste -> Transpose
	7. Ctrl-a, Ctrl-c -> Paste in Notepad++
	8. Delete the last line with Reference
	9. Add to the end D and T (tab characters seem to be required):
	D	1	D	Deuterium	2.01410177811																																																									
	T	1	T	Tritium	3.01604928																																																									
	10. Save as "hsc_elements.txt"

	```

4. __Color Codes__

	```
	1. Open the "C:\HSC9\Help\28 HSC - Databases.pdf" file
	2. Copy the Color codes to Notepad++
	3. Save as "hsc_color_codes.txt"
	```

5. __Units__

	```
	1. Open the elements.xlsx file saved in step 3
	2. Select the Columns A an B, Ctrl-c -> in the new Excel document Paste Special... -> Values
	3. Insert the Column before Column A
	4. Copy from Column B or Type short names in the Column A
	5. Rename the columns in the first line to
		 |        A        |       B        |  C  |
		1|PropertyShortName|PropertyFullName|Units|
	6. Delete empty or duplicate lines
	7. Save as "hsc_units.txt"
	```

## License

__HSCtoSQL__ is licensed under the GNU General Public License Version 3.
Modification or redistribution is permitted under the conditions of these license.

