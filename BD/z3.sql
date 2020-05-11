SELECT pp.Name, pc.Name FROM Production.Product as pp
    JOIN Production.ProductSubcategory as ps
        ON pp.ProductSubcategoryID = ps.ProductSubcategoryID
JOIN Production.ProductCategory as pc
ON ps.ProductCategoryID = pc.ProductCategoryID;


SELECT pc.Name, COUNT(pv.ProductID) FROM Production.Product as pp
JOIN Production.ProductSubCategory as ps
    ON pp.ProductSubcategoryID = ps.ProductSubcategoryID
JOIN Production.ProductCategory as pc
    ON ps.ProductCategoryID = pc.ProductCategoryID
JOIN Purchasing.ProductVendor as pv
    ON pv.ProductID = pp.ProductID
GROUP BY pc.Name
ORDER BY COUNT(pv.ProductID)