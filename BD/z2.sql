/*SELECT Color, COUNT(*) FROM Production.Product WHERE ListPrice < 30 GROUP BY Color;

SELECT Color FROM Production.Product GROUP BY Color HAVING MIN(ListPrice) > 100;

SELECT ProductCategoryID as 'Category', COUNT(*) as 'Amount' FROM Production.ProductSubcategory GROUP BY ProductCategoryID;

SELECT ProductID, SUM(OrderQty) as 'Sold' FROM Sales.SalesOrderDetail GROUP BY ProductID;

SELECT ProductID, SUM(OrderQty) as 'Sold' FROM Sales.SalesOrderDetail GROUP BY ProductID HAVING SUM(OrderQty) > 5;

SELECT CustomerID, CONVERT(char(11), OrderDate), COUNT(*) as 'Amount' FROM Sales.SalesOrderHeader GROUP BY CustomerID, CONVERT(char(11), OrderDate) HAVING COUNT(*) > 1;

SELECT SalesOrderID, COUNT(*) as 'Amount' FROM Sales.SalesOrderDetail GROUP BY SalesOrderID HAVING COUNT(*) > 3;

SELECT ProductID, Count(*) as 'Amount' FROM Sales.SalesOrderDetail GROUP BY ProductID HAVING COUNT(*) > 3;

SELECT ProductID, Count(*) as 'Amount' FROM Sales.SalesOrderDetail GROUP BY ProductID HAVING COUNT(*) = 3 OR COUNT(*) = 5;
*/
