// Group 6's Instashop Project 
// By: Basmala Kamal, Mohamed Ragab, Mohammed Sheemy, and Youssef Aboushady

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
// class for one individual product
// By: Youssef Aboushady
class OneProduct{
    private:
        struct Product{
                int pid;
                string pname;
                string pcategory;
                float pprice;
                int pquantity;
        };
    public:
    // creating an instance of the product to link with supermarket	
    Product item;
    // setter function
       void  SetProductDetails(int sid, string sname, string scategory, float sprice, int squantity){
            item.pid = sid;
            item.pname = sname;
            item.pcategory = scategory;
            item.pprice = sprice;
            item.pquantity = squantity;
        }
        // getter functions
        int GetID(){
            return item.pid;
        }
        
        void GetName(){
            cout << item.pname;
        }

        void GetCategory(){
            cout << item.pcategory;
        }
        
        float GetPrice(){
            return item.pprice;
        }

        int GetQuantity(){
            return item.pquantity;
        }
        
        void ChangeQuantity(int new_quantity){
            item.pquantity = new_quantity;
        }
        
};
// supermarket database
// By: Youssef Aboushady
class Supermarket{
    private:
        int sind;
        
    public:
    // array of 1000 product items
        OneProduct prdb[1000];
        // constructor that loads product database from file when program runs
        Supermarket(){
            load_products();
        }
    // destructor that saves product database to file when program ends
    ~Supermarket(){
        save_products();
    }
    	// function to load product data from file
        void load_products(){
            sind=0;
            ifstream reader;
            reader.open("product_data.txt");
            while(reader >> prdb[sind].item.pid){
                 reader>>prdb[sind].item.pname >> prdb[sind].item.pcategory >> prdb[sind].item.pprice >> prdb[sind].item.pquantity;
                sind++;
            }
            reader.close();
        }
        // adding to database - accessed through admin user
        void AddProduct(string add_name, string add_category, int add_price, int add_quantity){
            prdb[sind].SetProductDetails(sind, add_name, add_category, add_price, add_quantity);
            sind++;
        }
        // editing database - accessed through admin user    
        void EditProduct(int edit_id, string edit_name, string edit_category, int edit_price, int edit_quantity){
            for(int i=0;i<sind;i++){
                if(prdb[i].item.pid == edit_id){
                    prdb[i].SetProductDetails(edit_id, edit_name, edit_category, edit_price, edit_quantity);
                }
            }
        }
        // adjusting the quantity of an existing product - accessed through admin user
        void ChangeProductQuantity(int change_id, int new_quantity){
            for(int i=0;i<sind;i++){
                if(prdb[i].item.pid == change_id){
                    prdb[i].ChangeQuantity(new_quantity);
                }
            }
        }
    	// sorting product items by category
        void Sort(){
            for(int i=0;i<sind;i++){
                for(int j=0;j<sind;j++){
                    if(prdb[i].item.pcategory < prdb[j].item.pcategory){
                        swap(prdb[i], prdb[j]);
                    }
                }
            }
        }
    	// adjusting the quantity of an existing product - accessed through admin user
        void DisplayProducts(){
            cout << "AVAILABLE PRODUCTS \n====================" << endl;
            for(int i=0;i<sind;i++){
                    cout << "ID: " << prdb[i].item.pid << endl;
                    cout << "Name: " << prdb[i].item.pname << endl;
                    cout << "Category: " << prdb[i].item.pcategory << endl;
                    cout << "Price: " << prdb[i].item.pprice << endl;
                    cout << "Quantity: " << prdb[i].item.pquantity << endl;
                    cout << "====================" << endl;
            }
        }
        // saving product database       
        void save_products(){
            ofstream writer;
            writer.open("product_data.txt");
            for(int i=0;i<sind;i++){
                writer << prdb[i].item.pid << ' ' << prdb[i].item.pname << ' ' << prdb[i].item.pcategory << ' ' << prdb[i].item.pprice << ' ' << prdb[i].item.pquantity << endl;
            }
            writer.close();
        }
 
        OneProduct get_product(int i){
            return prdb[i];
        }
        // function to locate product in database
        int FindInSupermarket(int id){
            for(int i=0;i<sind;i++){
                if(prdb[i].GetID() == id){
                    return i;
                }
            }
            return -1;
        }          
};

// By: Mohamed Ragab
class cart{
    private:
    	// cart is array of products
        OneProduct Cart[30];
        int size;
        float totalprice;
    public:
            cart(){
            size = 0;
            totalprice = 0;
        }
        // function to determine index of product 
        int FindInCart(int id){
            for(int i=0;i<size;i++){
                if(Cart[i].GetID() == id){
                    return i;
                }
            }
            return -1;
        }
		// adds product to cart
        void AddToCart(int addq, OneProduct s){
            int x=FindInCart(s.GetID());
            if(x>-1)
            {
                 Cart[x].ChangeQuantity(addq+Cart[x].GetQuantity());
             }
             else
             {
                Cart[size]=s;
                Cart[size].ChangeQuantity(addq);
                size++;
             }
        }
		// removes product from cart
        bool RemoveFromCart(int id, int rmvq){
            int index = FindInCart(id);
            if(rmvq==Cart[index].GetQuantity())
            {
              Cart[index]=Cart[size];
              size--;
              return true;
              }
              else if(rmvq>Cart[index].GetQuantity())
              {
               return false;
               }
              else{
                   Cart[index].ChangeQuantity(Cart[index].GetQuantity()-rmvq);
                    return true;
               }
        }
        // calculates total price of products in cart
        float CalculateCartPrice(){
            totalprice = 0;
            for(int i=0; i<size; i++){
                totalprice += Cart[i].item.pprice * Cart[i].item.pquantity;
            }
            return totalprice;
        }
        // returns total cart price 
        float GetCartPrice(){
            return totalprice;
        }
        // displays current cart
        void DisplayCart(){
            cout << "CART\n====================" << endl;
            for(int i=0; i<size; i++){
                cout << "ID: " << Cart[i].item.pid << endl;
                cout << "Name: " << Cart[i].item.pname << endl;
                cout << "Category: " << Cart[i].item.pcategory << endl;
                cout << "Price: " << Cart[i].item.pprice << " EGP" << endl;
                cout << "Quantity: " << Cart[i].item.pquantity << endl;
                cout << "====================" << endl;
            }
            CalculateCartPrice();
            cout << "Total: " << GetCartPrice() << " EGP" << endl;
        }
        
};

// By: Mohammed Sheemy
class Wallet{
    private:
    struct debit{
        string cardHolder;
        int Number;
        float Balance;
    };
    public:
    	// creating an instance of type debit
        debit card;
        // init constructor
        Wallet(){
            card.cardHolder = "N/A";
            card.Number = 0;
            card.Balance = 0;
        }
        // parameterized constructor to set private attributes of struct
        Wallet(string Name, int n, float bal){
            card.cardHolder = Name;
            card.Number = n;
            card.Balance = bal;
        }
        // editing user's wallet info 
        void EditWallet(string Name, int n, float bal){
            card.cardHolder = Name;
            card.Number = n;
            card.Balance = bal;
        }
        // displaying user's wallet details
        void DisplayWallet(){
            cout << "Card Holder: " << card.cardHolder << endl;
            cout << "Card Number: " << card.Number << endl;
            cout << "Balance: " << card.Balance << " EGP" << endl;
        }
        // function to decrease user's balance by cart price through their choice to pay by debit
        void ProceedPayment(int price){
            if(card.Balance >= price){
                card.Balance -= price;
                cout << "Payment successful. Your balance is now: " << card.Balance << " EGP." << endl;
            }
            else{
                cout << "Payment unsuccessful. Please pay " << price << " EGP in cash on delivery." << endl;
            }
        }
        // charge the card with added balance by user
        void AddBalance(float amount){
            card.Balance += amount;
        }
        void SetBalance(float bal){
            card.Balance = bal;
        }
        
        float GetBalance(){
            return card.Balance;
        }
    
};

// collective user database
// By: Basmala Kamal
class userALL{
    private:
    	// user array index
        int num;
        // user object attributes
        struct User{
            int id;
            string name;
            int mobile;
            string email;
            string address;
            int password;
            cart usercart;
            Wallet userwallet;
        };
    
    public:
    	// creating an array of 100 users
        User users[100];
        // constructor to load user data when program begins
        userALL(){
            loadusers();
        }
        // destructor to save user data when program ends
	    ~userALL(){
	        saveusers();
	    }
	// function to load user data from file
    void loadusers()
    {
            num=0;
        ifstream load;
        load.open("user_data.txt");
        while(load>>users[num].id){
            load >>  users[num].name >> users[num].mobile >> users[num].email >> users[num].address >> users[num].password
                 >> users[num].userwallet.card.cardHolder >> users[num].userwallet.card.Number >> users[num].userwallet.card.Balance;
            num++;
        }
        load.close();
    }
    	// user registration
        void addUser(int ids, string names, int mobiles, string emails, string addresses, int passwords){
            if (num < 100){
                User news = {ids, names, mobiles, emails, addresses, passwords};
                users[num] = news;
                users[num].userwallet.EditWallet(names, ids, 0);
                num++;
            }
            else{
                cout << "Error: User database full." << endl;
            }
            
        }
        // user editing their details
        void editUser(int ids, string names, int mobiles, string emails, string addresses, int passwords){
            for (int i=0; i<num; i++){
                if (users[i].id == ids){
                    users[i].name = names;
                    users[i].mobile = mobiles;
                    users[i].email = emails;
                    users[i].address = addresses;
                    users[i].password = passwords;
                    users[i].userwallet.card.cardHolder = names;
                }
            }
        }
        // delete user from database         
        void deleteUser(int ids){
            for (int i=0; i<num; i++){
                if (users[i].id == ids){
                    for (int j = i; j < num-1; j++){
                        users[j-1] = users[j];
                    }
                    num--;
                }
            }
        }
        // user displaying their details
        void displayUser(int ind){
                    cout << "ID: " << users[ind].id << endl;
                    cout << "Name: " << users[ind].name << endl;
                    cout << "Mobile: " << users[ind].mobile << endl;
                    cout << "Email: " << users[ind].email << endl;
                    cout << "Address: " << users[ind].address << endl;
                    cout << "Balance: " << users[ind].userwallet.card.Balance << " EGP" << endl;
        }
        // invoking choosing the payment method as in delivery or by cart which invokes proceedpayment function
        void paymentMethod(int id, int payprice){
            users[id].userwallet.ProceedPayment(payprice);
        }
        // checking to see if login credentials match
        int login(string useremail, int userpassword){
            for(int i=0; i<=num; i++){
                if(useremail == users[i].email && userpassword == users[i].password){
                    return i;
                }
            }
            return -1;
        }
    // function to save user data to file
    void saveusers() {
        ofstream saver;
        saver.open("user_data.txt");
        for (int i = 0; i < num; i++) {
            saver << users[i].id << ' ' << users[i].name << ' ' << users[i].mobile << ' ' << users[i].email << ' ' << users[i].address << ' ' << users[i].password
                  << ' ' << users[i].userwallet.card.cardHolder << ' ' << users[i].userwallet.card.Number << ' ' << users[i].userwallet.card.Balance << endl;
        }
        saver.close();
    }
        // displaying user database
        void displayAllUsers(){
            for (int i=0; i<num; i++){
                    cout << "ID: " << users[i].id << endl;
                    cout << "Name: " << users[i].name << endl;
                    cout << "Mobile: " << users[i].mobile << endl;
                    cout << "Email: " << users[i].email << endl;
                    cout << "Address: " << users[i].address << endl;
                    cout << "Password: " << users[i].password << endl;
                }
            }
        
};

int main(){
    
    cart C;
    userALL userALL1;
    Supermarket data;
    data.Sort();
    char input, program = 'y';
    
        cout << "Enter 'r' to register, 'n' to login to an existing user." << endl;
        cin >> input;
        if(input == 'r'){
            cout << "Please enter your details in the following order: id, name, mobile, email, address, password." << endl;
            int inputid; string inputname; int inputmobile; string inputemail; string inputaddress; int inputpassword;
            cin >> inputid >> inputname >> inputmobile >> inputemail >> inputaddress >> inputpassword;
            userALL1.addUser(inputid, inputname, inputmobile, inputemail, inputaddress, inputpassword);
            cout << endl << "Registration complete. Proceeding to login." << endl;
        }
        
            cout << endl << "Enter 'a' for administrator, 'c' for customer." << endl;
            cin >> input;
            // login loop (does not exit until user logs in successfully)
            int checklogin=-1;
            while(checklogin == -1){
                string email; int password;
                cout << endl << "Email: ";
                cin >> email;
                cout << "Password: ";
                cin >> password;
                checklogin = userALL1.login(email, password);
                if(checklogin == -1){
                    cout << endl << "Login unsuccessful. Please try again." << endl;
                }
            }
                
                cout << endl << "Login successful! Welcome to Instashop, " << userALL1.users[checklogin].name << "." << endl;
                if(input == 'a'){
                	// admin interface
                    while(program == 'y'){
                        cout << "\n1: View database \n2: Add product \n3: Edit product details \n4: Change product quantity"
                             << "\n5: Display admin details \n6: Edit admin details \n7: Logoff" << endl;
                        int a1=0;
                        cin >> a1;
                        
                        if(a1==1){
                        cout << "Current database:\n\n";
                        data.DisplayProducts();
                        }
                    
                        else if(a1==2){
                            cout << "Enter new product name, category, price, and quantity." << endl;
                            string new_name; string new_category; float new_price; int new_quantity;
                            cin >> new_name >> new_category >> new_price >> new_quantity;
                            data.AddProduct(new_name, new_category, new_price, new_quantity);
                        }
                        
                        else if(a1==3){
                            cout << "Enter existing product id and updated name, category, price, and quantity." << endl;
                            int check_id; string new_name; string new_category; float new_price; int new_quantity;
                            cin >> check_id >> new_name >> new_category >> new_price >> new_quantity;
                            data.EditProduct(check_id, new_name, new_category, new_price, new_quantity);
                            cout << endl << "Product details updated successfully." << endl;
                        }
                        
                        else if(a1==4){
                            cout << "Enter product id and new quantity." << endl;
                            int check_id; int new_quantity;
                            cin >> check_id >> new_quantity;
                            data.ChangeProductQuantity(check_id, new_quantity);
                        }
                    
                        else if(a1==5){
                            cout << endl << "Admin details: " << endl;
                            userALL1.displayUser(checklogin);
                        }
                        
                        else if(a1==6){
                            cout << "Enter updated admin name, mobile, email, address, and password. " << endl;
                            string inputname; int inputmobile; string inputemail; string inputaddress; int inputpassword;
                            cin >> inputname >>  inputmobile >> inputemail >> inputaddress >> inputpassword;
                            userALL1.editUser(userALL1.users[checklogin].id, inputname, inputmobile, inputemail, inputaddress, inputpassword);
                            cout << endl << "Admin details updated successfully." << endl;
                        }
                        
                        else if(a1==7){
                            cout << endl << "Do you want to continue?" << endl;
                            cin >> program;
                        }
                                        
                        else{
                            cout << endl << "Please enter a valid number." << endl;
                        }
                    }
                }
                
                else if(input == 'c'){
                	// customer interface
                    while(program == 'y'){
                        cout << "\n1: View products \n2: View cart \n3: Add to cart \n4: Remove from cart \n5: Checkout"
                             << "\n6: Display user details \n7: Edit user details \n8: Delete user \n9: Display wallet details"
                             << "\n10: Add money to wallet \n11: Logoff" << endl;

                        int a1=0;
                        cin >> a1; cout << endl;
                        
                        if(a1==1){
                            data.DisplayProducts();
                        }
                    
                        else if(a1==2){
                            cout << "Here is your cart:" << endl << endl;
                            C.DisplayCart();
                        }
                        
                        else if(a1==3){
                            cout << "Enter the id and quantity of the product you would like to add to your cart." << endl;
                            int add_id; int add_quantity;
                            cin >> add_id >> add_quantity;
                            if((data.get_product(data.FindInSupermarket(add_id)).GetQuantity()>=add_quantity))
                            {
                                data.prdb[data.FindInSupermarket(add_id)].ChangeQuantity(data.prdb[data.FindInSupermarket(add_id)].GetQuantity()-add_quantity);
                                C.AddToCart(add_quantity, data.get_product(data.FindInSupermarket(add_id)));
                                cout << endl << add_quantity << ' ' << data.prdb[data.FindInSupermarket(add_id)].item.pname << " were added to your cart." << endl;
                             }
                            else
                            {
                                cout << endl << "Insufficient product quantity. Please try again." << endl;
                                }

                        }

                        else if(a1==4){
                            cout << "Enter the id and quantity of the product you would like to remove from your cart." << endl;
                            int rmv_id; int rmv_quantity;
                            cin >> rmv_id >> rmv_quantity;
                            bool rmv = C.RemoveFromCart(rmv_id, rmv_quantity);
                            if(rmv){
                                data.prdb[data.FindInSupermarket(rmv_id)].ChangeQuantity(data.prdb[data.FindInSupermarket(rmv_id)].GetQuantity()+rmv_quantity);
                            	cout << endl << rmv_quantity << ' ' << data.prdb[data.FindInSupermarket(rmv_id)].item.pname << " were removed from your cart." << endl;
                            }
                            else{
                           		cout << endl << "Failed to remove from cart. Please try again." << endl;
                            }
                        }

                        else if(a1==5){
                            char x;
                            cout << endl << "Here is your cart: " << endl << endl; C.DisplayCart();
                            cout << endl << "Would you like to pay by debit?" << endl;
                            cin >> x;
                            if (x=='y' || x=='Y'){
                                cout << endl << "Proceeding to payment." << endl;
                                userALL1.paymentMethod(checklogin, C.GetCartPrice());
                            }
                            else if (x=='n'||x=='N'){
                                cout << endl << "You will be charged " << C.GetCartPrice() << " EGP on delivery." << endl;
                            }
                            else{
                                cout << "Please enter a valid letter." << endl;
                            }
                            cout << "Do you want to continue?" << endl;
                            cin >> program;
                        }

                        else if(a1==6){
                            userALL1.displayUser(checklogin);
                        }

                        else if(a1==7){
                            cout << "Please enter updated user name, mobile, email, address, and password." << endl;
                                string inputname; int inputmobile; string inputemail; string inputaddress; int inputpassword;
                                cin >> inputname >> inputmobile >> inputemail >> inputaddress >> inputpassword;
                                userALL1.editUser(userALL1.users[checklogin].id, inputname, inputmobile, inputemail, inputaddress, inputpassword);
                                cout << "User details updated successfully." << endl;
                        }
                        
						else if (a1==8){
							char confirm;
							cout << endl << "Are you sure you want to delete your user?" << endl;
							cin >> confirm;
							if(confirm == 'y'){
								userALL1.deleteUser(checklogin);							
								cout << endl << "Your user has been deleted successfully." << endl;
								break;	
							}
							else{
								
							} 
						}

                        else if(a1==9){
                            cout << "Wallet details: " << endl;
                            userALL1.users[checklogin].userwallet.DisplayWallet();
                        }

                        else if(a1==10){
                            cout << "Your current balance is " << userALL1.users[checklogin].userwallet.card.Balance << " EGP. "
                                 << "How much would you like to add? ";
                            int add_bal;
                            cin >> add_bal;
                            userALL1.users[checklogin].userwallet.AddBalance(add_bal);
                            cout << "Your balance is now " << userALL1.users[checklogin].userwallet.card.Balance << " EGP." << endl;
                        }

                        else if(a1==11){
                            cout << "Do you want to continue?" << endl;
                            cin >> program;
                        }

                        else{
                            cout << "Please enter a valid number." << endl;
                        }
                    }
                }
    cout << endl << "Thank you for visiting Instashop. Have a nice day."<<endl;
}
