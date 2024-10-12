#include <iostream>     // Input-output stream header file
#include <ctime>       // Time-related functions header file
#include <map>         // Map data structure header file
#include <string>      // String data type header file
#include <cstdlib>     // Standard library for random number generation
#include <stdexcept>   // Standard library for exceptions

// Function to get the current time in HH:MM:SS format
std::string getCurrentTime() {
    time_t now = time(0);  // Get the current time
    tm* ltm = localtime(&now);  // Convert the time to local time

    std::string hours = (ltm->tm_hour < 10) ? "0" + std::to_string(ltm->tm_hour) : std::to_string(ltm->tm_hour);
    std::string minutes = (ltm->tm_min < 10) ? "0" + std::to_string(ltm->tm_min) : std::to_string(ltm->tm_min);
    std::string seconds = (ltm->tm_sec < 10) ? "0" + std::to_string(ltm->tm_sec) : std::to_string(ltm->tm_sec);

    return hours + ":" + minutes + ":" + seconds;  // Return the time in HH:MM:SS format
}

// Function to generate a 6-digit OTP for secure missile checkout
std::string generateOTP() {
    srand(static_cast<unsigned int>(time(0)));  // Seed for random number generation
    std::string otp = "";
    for (int i = 0; i < 6; i++) {
        otp += (rand() % 10) + '0';  // Generate a random digit and append it to the OTP
    }
    return otp;
}

// Function to verify an OTP
bool verifyOTP(const std::string& otp, const std::string& enteredOtp) {
    return otp == enteredOtp;
}

// Function to check missile availability in the inventory
void checkMissileAvailability(const std::map<std::string, int>& inventory, const std::string& missileName) {
    if (inventory.find(missileName) != inventory.end()) {
        if (inventory.at(missileName) > 0) {
            std::cout << missileName << " is available. Stock: " << inventory.at(missileName) << std::endl;
        } else {
            std::cout << missileName << " is out of stock!" << std::endl;
        }
    } else {
        std::cout << "Missile not found in the inventory!" << std::endl;
    }
}

// Function to checkout a missile from the inventory
void checkoutMissile(std::map<std::string, int>& inventory, const std::string& missileName) {
    if (inventory.find(missileName) != inventory.end()) {
        if (inventory.at(missileName) > 0) {
            std::string otp = generateOTP();
            std::cout << "OTP displayed on deck monitor: " << otp << std::endl;

            std::string enteredOtp;
            std::cout << "Enter the OTP: ";
            std::cin >> enteredOtp;

            // Verify the OTP before allowing missile checkout
            if (verifyOTP(otp, enteredOtp)) {
                std::string coordinates;
                std::cout << "Enter the launch coordinates (latitude and longitude): ";
                std::cin >> coordinates;

                std::cout << "Select a reason for launching the missile:\n";
                std::cout << "1. To attack enemy\n";
                std::cout << "2. For trial\n";
                std::cout << "3. For self-defense\n";
                int reasonChoice;
                std::cout << "Enter your choice (1-3): ";
                std::cin >> reasonChoice;

                std::string reason;
                switch (reasonChoice) {
                    case 1:
                        reason = "To attack enemy";
                        break;
                    case 2:
                        reason = "For trial";
                        break;
                    case 3:
                        reason = "For self-defense";
                        break;
                    default:
                        reason = "Unknown reason";
                        break;
                }

                std::cout << "Launching " << missileName << " at coordinates: " << coordinates 
                          << " for reason: " << reason << std::endl;

                inventory[missileName]--;  // Reduce stock by 1
                std::cout << missileName << " checked out successfully. Remaining stock: " 
                          << inventory.at(missileName) << std::endl;
                std::cout << "Checkout Time: " << getCurrentTime() << std::endl;
            } else {
                std::cout << "Incorrect OTP! Missile checkout failed." << std::endl;
            }
        } else {
            std::cout << missileName << " is out of stock!" << std::endl;
        }
    } else {
        std::cout << "Missile not found in the inventory!" << std::endl;
    }
}

// Function to return a missile to the inventory
void returnMissile(std::map<std::string, int>& inventory, const std::string& missileName) {
    if (inventory.find(missileName) != inventory.end()) {
        inventory[missileName]++;  // Increment stock by 1
        std::cout << missileName << " returned successfully. Updated stock: " << inventory.at(missileName) << std::endl;
    } else {
        std::cout << "Missile not found in the inventory!" << std::endl;
    }
}

int main() {
    std::map<std::string, int> missileInventory;  // Map to store missile inventory (missile name, stock quantity)
    std::string missileName;
    int choice;

    // Initialize missile inventory with missile names and stock quantities
    missileInventory["BrahMos"] = 10;
    missileInventory["Prithvi"] = 5;
    missileInventory["Agni"] = 7;
    missileInventory["Nirbhay"] = 4;

    std::cout << "Welcome to the Missile Inventory Management System." << std::endl;

    do {
        std::cout << "\n1. Check Missile Availability" << std::endl;
        std::cout << "2. Checkout Missile" << std::endl;
        std::cout << "3. Return Missile" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the name of the missile (e.g., BrahMos, Prithvi): ";
                std::cin >> missileName;
                checkMissileAvailability(missileInventory, missileName);  // Check if the missile is available in inventory
                break;

            case 2: {
                std::string captainPassword;  // Declare inside the case scope
                std::cout << "Enter Captain's Password: ";
                std::cin >> captainPassword;

                // Check the captain's password (hardcoded for demonstration)
                if (captainPassword == "captain123") {
                    std::cout << "Enter the name of the missile to checkout: ";
                    std::cin >> missileName;
                    checkoutMissile(missileInventory, missileName);  // Checkout the missile from the inventory
                } else {
                    std::cout << "Invalid password! Access denied." << std::endl;
                }
                break;
            }

            case 3:
                std::cout << "Enter the name of the missile to return: ";
                std::cin >> missileName;
                returnMissile(missileInventory, missileName);  // Return the missile to the inventory
                break;

            case 4:
                std::cout << "Exiting the system. Have a good day!" << std::endl;
                break;

            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
