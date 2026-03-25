#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef struct
{
    std::string name;
    unsigned int price;
    unsigned int quantity;
} Product;

void showAllProducts(std::vector<Product> products) {
    if (products.empty()) {
        std::cout << "There are no products.\n";
        return;
    }
    std::cout << "Showing all products:\n";
    for (int i = 0; i < products.size(); i++) {
        Product product = products[i];
        int zl = product.price / 100;
        int gr = product.price % 100;
        std::cout << "\t[" << i << "] " << product.name << " (" << zl << "." << gr << "zl) - " << product.quantity << "\n";
    }
}

std::vector<Product> addProduct(std::vector<Product> products, const std::string name, int price, int quantity) {
    if (name == "") {
        std::cerr << "Error: Name could not be empty.\n";
        return products;
    }
    else if (price < 0) {
        std::cerr << "Error: Price could not be negative.\n";
        return products;
    }
    else if (quantity < 0) {
        std::cerr << "Error: quantity could not be negative.\n";
        return products;
    }

    Product product = {name, (unsigned int)price, (unsigned int)quantity};
    products.push_back(product);
    return products;
}

std::vector<Product> removeProduct(std::vector<Product> products, int index) {
    if ((index < 0) || (index >= products.size())) {
        std::cerr << "Error: Product index is out of range.\n";
        return products;
    }

    products.erase(products.begin() + index);
    return products;
}

std::vector<Product> setProductQuantity(std::vector<Product> products, int index, int quantity) {
    if ((index < 0) || (index >= products.size())) {
        std::cerr << "Error: Product index is out of range.\n";
        return products;
    }
    else if (quantity < 0) {
        std::cerr << "Error: quantity could not be negative.\n";
        return products;
    }

    products[index].quantity = quantity;
    return products;
}

void findProductByName(std::vector<Product> products, const std::string query) {
    for (int i = 0; i < products.size(); i++) {
        Product product = products[i];
        if (product.name == query) {
            std::cout << "Product index is: " << i << "\n";
            return;
        }
    }
    std::cout << "Product was not found.\n";
}

void saveProductsToFile(const std::string filename, std::vector<Product> products) {
    std::ofstream file = std::ofstream(filename);

    for (Product product : products) {
        file << product.name << " " << product.price << " " << product.quantity << "\n";
    }

    file.close();
}

std::vector<Product> loadProductsFromFile(const std::string filename) {
    std::vector<Product> products = {};
    std::ifstream file = std::ifstream(filename);

    Product product;
    while (file >> product.name >> product.price >> product.quantity) {
        products.push_back(product);
    }

    file.close();
    return products;
}

int main(int argc, char* argv[]) {
    std::string productsFilename = (argc < 2) ? "magazyn.txt" : argv[1];

    std::vector<Product> products = loadProductsFromFile(productsFilename);

    bool running = true; 
    while (running)
    {
        std::cout 
            << "\nChoose action:\n"
            << "\t1: Show all products\n"
            << "\t2: Add product\n"
            << "\t3: Remove product\n"
            << "\t4: Change product quantity\n"
            << "\t5: Find product by name\n"
            << "\t6: End program\n";
        
        int action;
        std::cin >> action;
        std::cout << "\n";
        std::string name;
        int price;
        int quantity;
        int index;
        switch (action)
        {
            case 1:
                showAllProducts(products);
                break;
            case 2:
                std::cout << "Enter product name: ";
                std::cin >> name;
                std::cout << "Enter product price: ";
                std::cin >> price;
                std::cout << "Enter product quantity: ";
                std::cin >> quantity;
                products = addProduct(products, name, price, quantity);
                break;
            case 3:
                std::cout << "Enter product index: ";
                std::cin >> index;
                products = removeProduct(products, index);
                break;
            case 4:
                std::cout << "Enter product index: ";
                std::cin >> index;
                std::cout << "Enter new product quantity: ";
                std::cin >> quantity;
                products = setProductQuantity(products, index, quantity);
                break;
            case 5:
                std::cout << "Enter product name: ";
                std::cin >> name;
                findProductByName(products, name);
                break;
            case 6:
                std::cout << "Exiting program.\n";
                running = false;
                break;
            default:
                std::cerr << "Error: Invalid action.\n";
                break;
        }
    }

    saveProductsToFile(productsFilename, products);

    return 0;
}