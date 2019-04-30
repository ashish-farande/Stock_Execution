#include "StockOrder/StockOrder.h"
#include "LogHandler/CSVLogger.h"
#include <assert.h>
#include <iostream>

StockOrder::StockOrder(StockID stockID, std::string companyName, orderSide side, Quantity quantity) : _stockID(stockID), _companyName(companyName), _side(side), _quantity(quantity), _remainingQuantity(quantity), _status(orderStatus::OPEN)
{
    CSVLogger::getInstance().writeTheOrder(*this);
}

void StockOrder::closeOrder()
{
    assert(_status == orderStatus::OPEN);
    _status = orderStatus::CLOSED;
    CSVLogger::getInstance().changeStatus(*this);
}

const StockID StockOrder::getStockID() const
{
    return _stockID;
}

const std::string &StockOrder::getCompanyName() const
{
    return _companyName;
}

const orderSide StockOrder::getSide() const
{
    return _side;
}

const Quantity StockOrder::getQuantity() const
{
    return _quantity;
}

const orderStatus StockOrder::getStatus() const
{
    return _status;
}

const Quantity  StockOrder::getRemainingQuantity() const
{
    return _remainingQuantity;
}

void StockOrder::reduceRemainingQuantity(Quantity quantity)
{
    assert(quantity <= _remainingQuantity);
    _remainingQuantity -= quantity;
    if (_remainingQuantity == 0)
        closeOrder();
    else
        CSVLogger::getInstance().changeStatus(*this);
}

void StockOrder::printOrder()
{
    std::cout << "========================================================================" << std::endl;
    std::cout << "The StockID is: " << _stockID << std::endl;
    std::cout << "The Order side is: " << (_side ? "Sell" : "Buy") << std::endl;
    std::cout << "The Company Name is: " << _companyName << std::endl;
    std::cout << "The Quantity is: " << _quantity << std::endl;
    std::cout << "The Remaining is: " << _remainingQuantity << std::endl;
    std::cout << "The Status is: " << (_status ? "CLOSED" : "OPEN") << std::endl;
    std::cout << "========================================================================" << std::endl;
}
