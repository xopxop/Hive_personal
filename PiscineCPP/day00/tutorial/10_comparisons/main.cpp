/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 16:23:44 by dthan             #+#    #+#             */
/*   Updated: 2020/04/19 16:23:45 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample.class.hpp"

int main() {
	Sample instance1 (42);
	Sample instance2 (42);

	if (&instance1 == &instance1)
		std::cout << "instance1 and instance1 are physically equal" << std::endl;
	else
		std::cout << "instance1 and instance1 are not physically equal" << std::endl;
	
	
	if (&instance1 == &instance2)
		std::cout << "instance1 and instance2 are physically equal" << std::endl;
	else
		std::cout << "instance1 and instance2 are not physically equal" << std::endl;
	
	if (instance1.compare(&instance1) == 0)
		std::cout << "instance1 and instance1 are structurally equal" << std::endl;
	else
		std::cout << "instance1 and instance1 are not structurally equal" << std::endl;
	
	if (instance1.compare(&instance2) == 0)
		std::cout << "instance1 and instance2 are structurally equal" << std::endl;
	else
		std::cout << "instance1 and instance2 are not structurally equal" << std::endl;

	return 0;
}
