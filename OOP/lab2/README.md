# Лабораторная #2 по ООП на Котлине

### [Условие](https://reports.artrey.ru/task/8/)

## Использование

* Создайте экземпляр класса `Shop`
    ```
    val store = Store("Pyaterochka", "41, Kronverskaya st.")
    ```
  
* Создайте экземпляр класса `Product`
    ```
    val product = Product("Pizza")
    ```
  
* Для того, чтобы завести товары с магазин, вызовите метод Store.deliverSupply
    ```
    val consignment = ShopReceipt()
    consignment.push(product1, product1Amount, product1Price)
    consignment.push(product2, product2Amount, product2Price)
    store.deliverSupply(consignment)
    ```
  
* Для того, чтобы найти магазин с самым дешевым товаром, вызовите статик метод Store.findCheapestProduct
    ```
    val store = Store.findCheapestProduct(product)
    ```
  
* Для того, чтобы узнать, что вы можете купить на какое-то количество денег, вызовите статик метод Store.analysePrice
    ```
    val receipt = store.analysePrice(moneyAmount)
    ```
  
* Для того, чтобы узнать цену ваших покупок в каком-то магазине, вызовите метод Store.buy
    ```
    val consignment = ShopReceipt()
    consignment.push(product1, product1Amount)
    consignment.push(product2, product2Amount)
    val price = store.buy(consignment)
    ```
  
* Для того, чтобы узнать магазин с самыми дешевыми покупками, вызовите статик метод Store.findCheapestProducts
    ```
    val consignment = ShopReceipt()
    consignment.push(product1, product1Amount)
    consignment.push(product2, product2Amount)
    val store = Store.findCheapestProducts(consignment)
    ```
