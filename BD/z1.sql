/* SELECT Name, Color, Size FROM Production.Product */

/* SELECT Name, Color, Size FROM Production.Product WHERE ListPrice > 100 */

/* SELECT Name, Color, Size FROM Production.Product WHERE ListPrice < 100 AND COLOR = 'Black' */

/* SELECT Name, Color, Size FROM Production.Product WHERE ListPrice < 100 AND COLOR = 'Black' ORDER BY ListPrice */

/* SELECT TOP 3 Name, Color, Size FROM Production.Product WHERE COLOR LIKE 'Black' ORDER BY ListPrice DESC */

/* SELECT Name, Color FROM Production.Product WHERE Color != 'NA' AND Size IS NOT NULL */

/* SELECT Distinct Color FROM Production.Product WHERE 10 <= ListPrice AND ListPrice <= 50 */

/* SELECT Color FROM Production.Product WHERE Name LIKE 'L_N%' */

/* SELECT Name FROM Production.Product WHERE Name LIKE '[DM]___%' */

/* SELECT Name, SellStartDate FROM Production.Product WHERE DATEPART(YEAR, SellStartDate) <= 2012 */

/* SELECT Name FROM Production.ProductSubcategory */

/* SELECT Name FROM Production.ProductCategory */

/* SELECT FirstName FROM Person.Person WHERE Title = 'Mr.' */

/* SELECT FirstName FROM Person.Person WHERE Title IS NULL */
