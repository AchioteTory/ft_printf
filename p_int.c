#include "ft_printf.h"

static void	params_parsing(long long c, t_fmt *params)
{
	if (params->precision >= 0)
		params->zero = 0;
	if (c == 0 && params->precision == 0)
		params->precision = 0;
	else if (len(c) > params->precision)
		params->precision = len(c);
	if (params->width < 0)
	{
		params->minus = 1;
		params->zero = 0;
		params->width *= -1;
	}
	if (params->precision < 0)
		params->precision = 0;
}

static void	if_minus(long long c, int minus, t_fmt *params, int *printed)
{
	if (minus)
		ft_putchar_fd('-', 1);
	*printed += minus;
	while (params->precision - len(c) > 0)
	{
		ft_putchar_fd('0', 1);
		params->precision--;
		params->width--;
		*printed += 1;
	}
	if (!(c == 0 && params->precision == 0))
	{
		print_nbr(c, 1);
		*printed += len(c);
	}
	while (params->width - params->precision - minus > 0)
	{
		ft_putchar_fd(' ', 1);
		params->width--;
		*printed += 1;
	}
}

static void	if_zero(long long c, int minus, t_fmt *params, int *printed)
{
	if (minus)
		ft_putchar_fd('-', 1);
	*printed += minus;
	while (params->width - len(c) - minus > 0)
	{
		ft_putchar_fd('0', 1);
		params->width--;
		*printed += 1;
	}
	print_nbr(c, 1);
	*printed += len(c);
}

static void	if_not_zero(long long c, int minus, t_fmt *params, int *printed)
{
	if (params->width < params->precision)
		params->width = params->precision;
	while (params->width - params->precision - minus > 0)
	{
		ft_putchar_fd(' ', 1);
		params->width--;
		*printed += 1;
	}
	if (minus)
		ft_putchar_fd('-', 1);
	*printed += minus;
	while (params->precision - len(c) > 0)
	{
		ft_putchar_fd('0', 1);
		params->precision--;
		*printed += 1;
	}
	if (!(c == 0 && params->precision == 0))
	{
		print_nbr(c, 1);
		*printed += len(c);
	}
}

void	p_int(va_list arguments, t_fmt *params, int *printed)
{
	long long	c;
	int	minus;

	c = (long long)va_arg(arguments, int);
	minus = 0;
	if (c < 0)
		minus = 1;
	params_parsing(c, params);
	if (params->minus)
		if_minus(c, minus, params, printed);
	else
	{
		if (params->zero)
			if_zero(c, minus, params, printed);
		else
			if_not_zero(c, minus, params, printed);
	}
}
