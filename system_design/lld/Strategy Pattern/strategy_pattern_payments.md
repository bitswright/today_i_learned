# Strategy Pattern - Explained Simply with Payments Example

## What Problem Are We Solving?

Imagine you're building an online shopping app like Amazon or Flipkart. When a customer checks out, they can pay using different methods:

- Credit Card
- PayPal
- UPI (Google Pay, PhonePe)
- Cash on Delivery

**The Question:** How do you write code that handles all these payment methods cleanly?

---

## The Wrong Way (What Beginners Usually Do)

Most people start with a bunch of `if-else` statements:

```python
def checkout(cart, payment_method, details):
    total = sum(item.price for item in cart)
    
    if payment_method == "credit_card":
        # Credit card logic
        card_number = details["card_number"]
        cvv = details["cvv"]
        print(f"Charging ₹{total} to card ending in {card_number[-4:]}")
        # Connect to bank API...
        
    elif payment_method == "paypal":
        # PayPal logic
        email = details["email"]
        print(f"Charging ₹{total} to PayPal account {email}")
        # Connect to PayPal API...
        
    elif payment_method == "upi":
        # UPI logic
        upi_id = details["upi_id"]
        print(f"Requesting ₹{total} from UPI ID {upi_id}")
        # Connect to UPI API...
        
    elif payment_method == "cod":
        # Cash on Delivery logic
        print(f"Order placed. Pay ₹{total} when delivered.")
        
    else:
        print("Unknown payment method!")
```

### Why This Is Bad

| Problem | What Happens |
|---------|--------------|
| **Gets messy fast** | Add 5 more payment methods = 5 more `elif` blocks |
| **Hard to change** | Want to update UPI logic? Hope you don't break credit card code! |
| **Hard to test** | Can't test PayPal without also loading credit card code |
| **Violates "Open/Closed"** | Every new payment method = editing this function |

Think of it like a Swiss Army knife where all the tools are glued together. Want to sharpen the knife? Good luck not damaging the scissors!

---

## The Right Way: Strategy Pattern

### The Idea in Plain English

Instead of one giant function with all payment logic mixed together:

> **Put each payment method in its own separate box. The checkout process just asks the box to "pay" - it doesn't care what's inside the box.**

It's like having separate specialists:
- Credit Card Specialist
- PayPal Specialist  
- UPI Specialist

You just tell whichever specialist you need: "Handle this payment." They know what to do.

---

## Building It Step by Step

### Step 1: Create a "Contract" (What Every Payment Method Must Do)

First, we define what ANY payment method should be able to do. In Python, we use an "abstract class" - think of it as a template.

```python
from abc import ABC, abstractmethod

class PaymentStrategy(ABC):
    """
    This is like a job description.
    Any payment method MUST be able to do these things.
    """
    
    @abstractmethod
    def pay(self, amount):
        """Process the payment. Every payment method must implement this."""
        pass
    
    @abstractmethod
    def get_name(self):
        """Return the payment method name."""
        pass
```

**In simple terms:** This says "If you want to be a payment method, you MUST have a `pay()` function and a `get_name()` function."

---

### Step 2: Create Each Payment Method (The Strategies)

Now we create each payment method as its own class. Each one follows the "contract" above.

```python
class CreditCardPayment(PaymentStrategy):
    """Handles credit card payments."""
    
    def __init__(self, card_number, card_holder, cvv, expiry):
        self.card_number = card_number
        self.card_holder = card_holder
        self.cvv = cvv
        self.expiry = expiry
    
    def pay(self, amount):
        # In real life, this would connect to a bank API
        last_four = self.card_number[-4:]
        print(f"💳 Charging ₹{amount} to card ending in {last_four}")
        print(f"   Card holder: {self.card_holder}")
        print(f"   Status: Payment Successful!")
        return True
    
    def get_name(self):
        return "Credit Card"


class PayPalPayment(PaymentStrategy):
    """Handles PayPal payments."""
    
    def __init__(self, email):
        self.email = email
    
    def pay(self, amount):
        # In real life, this would connect to PayPal API
        print(f"🅿️ Charging ₹{amount} to PayPal account: {self.email}")
        print(f"   Status: Payment Successful!")
        return True
    
    def get_name(self):
        return "PayPal"


class UPIPayment(PaymentStrategy):
    """Handles UPI payments (Google Pay, PhonePe, etc.)."""
    
    def __init__(self, upi_id):
        self.upi_id = upi_id
    
    def pay(self, amount):
        # In real life, this would connect to UPI/NPCI API
        print(f"📱 Requesting ₹{amount} from UPI ID: {self.upi_id}")
        print(f"   Status: Payment Successful!")
        return True
    
    def get_name(self):
        return "UPI"


class CashOnDelivery(PaymentStrategy):
    """Handles Cash on Delivery."""
    
    def __init__(self, phone_number):
        self.phone_number = phone_number
    
    def pay(self, amount):
        print(f"🚚 Cash on Delivery selected")
        print(f"   Amount to pay on delivery: ₹{amount}")
        print(f"   Confirmation SMS sent to: {self.phone_number}")
        return True
    
    def get_name(self):
        return "Cash on Delivery"
```

**Notice:** Each payment method is completely independent. Credit card code knows nothing about PayPal. PayPal knows nothing about UPI. They're separate boxes!

---

### Step 3: Create the Shopping Cart (The "Context")

The shopping cart doesn't care HOW you pay. It just needs SOME payment method.

```python
class ShoppingCart:
    """
    The shopping cart that uses a payment strategy.
    It doesn't know the details of any payment method.
    It just knows "I have something that can pay."
    """
    
    def __init__(self):
        self.items = []
        self.payment_strategy = None  # Will be set later
    
    def add_item(self, name, price):
        """Add an item to the cart."""
        self.items.append({"name": name, "price": price})
        print(f"Added: {name} - ₹{price}")
    
    def get_total(self):
        """Calculate total price."""
        return sum(item["price"] for item in self.items)
    
    def set_payment_method(self, payment_strategy):
        """
        This is the key!
        We can swap payment methods anytime.
        """
        self.payment_strategy = payment_strategy
        print(f"\n✓ Payment method set to: {payment_strategy.get_name()}")
    
    def checkout(self):
        """Process the order."""
        if not self.items:
            print("Cart is empty!")
            return False
        
        if not self.payment_strategy:
            print("Please select a payment method!")
            return False
        
        total = self.get_total()
        print(f"\n{'='*50}")
        print(f"CHECKOUT - Total: ₹{total}")
        print(f"{'='*50}")
        
        # Here's the magic - we just call pay()
        # We don't care if it's credit card, PayPal, or anything else
        success = self.payment_strategy.pay(total)
        
        if success:
            print(f"\n🎉 Order placed successfully!")
            self.items = []  # Clear cart
        
        return success
```

**The Magic Line:** `self.payment_strategy.pay(total)`

The cart doesn't know or care how the payment happens. It just calls `.pay()` and the right thing happens!

---

### Step 4: See It In Action!

```python
def main():
    # Create a shopping cart
    cart = ShoppingCart()
    
    # Add some items
    print("🛒 ADDING ITEMS TO CART")
    print("-" * 30)
    cart.add_item("iPhone 15", 79900)
    cart.add_item("AirPods Pro", 24900)
    cart.add_item("Phone Case", 999)
    
    print(f"\nCart Total: ₹{cart.get_total()}")
    
    # ============================================
    # EXAMPLE 1: Pay with Credit Card
    # ============================================
    print("\n" + "=" * 50)
    print("EXAMPLE 1: Paying with Credit Card")
    print("=" * 50)
    
    credit_card = CreditCardPayment(
        card_number="4111222233334444",
        card_holder="Rahul Sharma",
        cvv="123",
        expiry="12/25"
    )
    cart.set_payment_method(credit_card)
    cart.checkout()
    
    # ============================================
    # EXAMPLE 2: Different cart, pay with UPI
    # ============================================
    print("\n" + "=" * 50)
    print("EXAMPLE 2: New cart, paying with UPI")
    print("=" * 50)
    
    cart2 = ShoppingCart()
    cart2.add_item("MacBook Air", 99900)
    
    upi = UPIPayment(upi_id="rahul@okaxis")
    cart2.set_payment_method(upi)
    cart2.checkout()
    
    # ============================================
    # EXAMPLE 3: Change payment method at runtime!
    # ============================================
    print("\n" + "=" * 50)
    print("EXAMPLE 3: Changing payment method")
    print("=" * 50)
    
    cart3 = ShoppingCart()
    cart3.add_item("Watch", 15000)
    
    # First, user selects PayPal
    paypal = PayPalPayment(email="rahul@gmail.com")
    cart3.set_payment_method(paypal)
    
    # User changes mind, wants Cash on Delivery instead
    print("\n[User changed their mind...]")
    cod = CashOnDelivery(phone_number="9876543210")
    cart3.set_payment_method(cod)
    
    cart3.checkout()


if __name__ == "__main__":
    main()
```

---

## What Did We Achieve?

### Before (If-Else Mess)
```
checkout()
├── if credit_card → 20 lines of card code
├── elif paypal → 15 lines of PayPal code
├── elif upi → 18 lines of UPI code
├── elif cod → 10 lines of COD code
└── elif crypto → ... (keeps growing!)
```

### After (Strategy Pattern)
```
ShoppingCart
└── payment_strategy.pay()  ← Just this one line!

CreditCardPayment.pay()  ← Separate file/class
PayPalPayment.pay()      ← Separate file/class
UPIPayment.pay()         ← Separate file/class
CashOnDelivery.pay()     ← Separate file/class
```

---

## Why Is This Better? (Benefits)

| Benefit | Explanation |
|---------|-------------|
| **Easy to add new payment methods** | Just create a new class. Don't touch existing code! |
| **Easy to test** | Test each payment method separately |
| **Easy to understand** | Each class does ONE thing |
| **Swap at runtime** | User can change payment method without restarting |
| **No messy if-else** | Clean, organized code |

---

## Visual Summary

```
    Customer selects payment
              │
              ▼
    ┌─────────────────┐
    │  Shopping Cart  │
    │                 │
    │  "I need to     │
    │   process a     │
    │   payment"      │
    └────────┬────────┘
             │
             │ Uses whichever strategy
             │ was set by the customer
             │
             ▼
    ┌─────────────────────────────────────────────┐
    │         PaymentStrategy (Contract)          │
    │         "Anyone who can pay()"              │
    └─────────────────────────────────────────────┘
             △       △       △       △
             │       │       │       │
    ┌────────┴─┐ ┌───┴───┐ ┌─┴──┐ ┌──┴──┐
    │Credit    │ │PayPal │ │UPI │ │ COD │
    │Card      │ │       │ │    │ │     │
    │          │ │       │ │    │ │     │
    │pay()     │ │pay()  │ │pay()│ │pay()│
    │connects  │ │calls  │ │calls│ │marks│
    │to bank   │ │PayPal │ │NPCI │ │order│
    └──────────┘ └───────┘ └────┘ └─────┘
```

---

## Key Vocabulary

| Term | Meaning |
|------|---------|
| **Strategy** | A specific way of doing something (e.g., CreditCardPayment) |
| **Context** | The class that uses strategies (e.g., ShoppingCart) |
| **Interface/Contract** | The rules that all strategies must follow (PaymentStrategy) |
| **Composition** | "Has a" relationship (Cart HAS a payment strategy) |

---

## Think About It

**Question:** What if you wanted to add Cryptocurrency payment?

**Answer:** Just create a new class!

```python
class CryptoPayment(PaymentStrategy):
    def __init__(self, wallet_address):
        self.wallet_address = wallet_address
    
    def pay(self, amount):
        btc_amount = amount / 5000000  # Fake conversion
        print(f"₿ Transferring {btc_amount:.6f} BTC from wallet")
        print(f"   Wallet: {self.wallet_address[:10]}...")
        return True
    
    def get_name(self):
        return "Cryptocurrency"
```

You didn't touch ShoppingCart, CreditCardPayment, or any other class! That's the power of Strategy Pattern.

---

## Complete Working Code

Copy everything above into a single file called `payments.py` and run it:

```bash
python payments.py
```

You'll see the different payment methods in action!
