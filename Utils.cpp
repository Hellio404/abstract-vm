/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:18:03 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/10 12:18:49 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

long long custom_stoll(const std::string &val)
{
    return std::stoll(val);
}

double custom_stod(const std::string &val)
{
    return std::stod(val);
}
