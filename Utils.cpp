/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:18:03 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/10 17:35:11 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

long long custom_stoll(const std::string &val)
{
    long long res = 0;
    try
    {
        res = std::stoll(val);
    }
    catch(const std::exception& e)
    {
        res = std::numeric_limits<long long>::max();
    }
    return res;
}

double custom_stod(const std::string &val)
{
    double res = 0;
    try
    {
        res = std::stod(val);
    }
    catch(const std::exception& e)
    {
        res = std::numeric_limits<double>::quiet_NaN();
    }
    return res;
}
