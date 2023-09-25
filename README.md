# Shop_Billing_Client-Server
In this Application, we launch the server to start the billing process.
Thereafter the Client(s) can connect to the server and as for the price of individual items and then finally get the total bill amount.

The Server is capable of handling 5 clients at the same time, without merging any of their request lists.

The requests that can be made from the client side are as follows:

1. The Program prompts you to enter the request, possible values: 0 and 1
     a. '0'- This means you want to continue with the purchase and add more items to the list.
     b. '1'- This means that you are done with your purchase and want to finalise the total bill amount.

2. Upon inserting '0' the program will ask you for the UPC(Unique-Product-Code) number.
     a. The UPC number is maintained in the Database.txt file which stores the name and price of all the items.
         I. When you enter a valid UPC the program will ask for the quantity.
         II. Entering the quantity will get you the rate of the item and the total price.
         III. The system will again ask for the option choice and you can follow step 1 again.
     b. In case of a wrong UPC input, you will get a prompt the UPC entered does not exist and you will again have the option to choose what you want to do.
4. If you choose '1' as the input, the program will return the total bill amount and display a thank you message, after which the connection terminates.
