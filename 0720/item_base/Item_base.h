#ifndef ITEM_BASE_H_
#define ITEM_BASE_H 

class Item_base{
    public:
        Item_base(const std::string &book = " ",
                       double sale_price = 0.0):
            isbn_(book), price_(sales_price){};
        std::string book() const
        {
            return isbn_;
        }
        virtual double net_price(size_t n)
        {
            return n * price_;
        }
        virtual ~Item_base();
    private:
        std::string isbn_;
    protected:
        double price_;
        
};

class Bulk_base : public Item_base
{
    public:
        Bulk_base(const std:: string &book = "",
                double price = 0,
                int min_qty = 0,
                double discount = 0):
            Item_base(book, price),
            min_qty_(min_qty),
            discount_(discount){}
        double net_price(size_t cnt)
        {
            if(cnt > min_qty_)
            {
                return cnt * price(1 - discount);
            }
            else
                return cnt * price;
        }
        virtual ~Bulk_base();
    private:
        int min_qty_;
        double discount_;
        
};

#endif  /*ITEM_BASE_H*/
