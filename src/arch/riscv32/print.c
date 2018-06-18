#include <stdbool.h>
#include "print.h"

volatile unsigned int* const UART0_ADDR = (unsigned int*)0x10000000;

bool is_digit_char(char c)
{
    return (c >= 48 && c <= 57) || (c >= 65 && c <= 70) || (c >= 95 && c <= 102);
}

bool is_number_char(char c)
{
    return c >= 48 && c <= 57;
}

int atoi(const char* const str)
{
    int number = 0;
    int temp_number = 0;
    int digit_index = 0;
    int str_index = 0;
    char chr;
    bool is_negative = false;
    while((chr = str[str_index++]) != '\0')
    {
        if(chr == '-' && digit_index == 0)
        {
            is_negative = true;
        }
        else if(is_digit_char(chr))
        {
            temp_number = chtoi(chr);
            number = digit_index == 0 ? temp_number : number * 10 + temp_number;
            digit_index += 1;
        }
        else
        {
            break;
        }
    }
    if(is_negative)
    {
        return number * -1;
    }
    else
    {
        return number;
    }
}

char* get_binary_string(int num, char* const buffer)
{
    bool start_adding = false;
    unsigned int bit_window = 0x80000000;
    int bit_window_index = 31;
    int buf_index = 0;
    int bit = 0;
    while(bit_window > 0)
    {
        bit = (num & bit_window) >> bit_window_index;
        start_adding |= bit;
        if(start_adding)
        {
            buffer[buf_index] = bit + 48;
            buf_index += 1;
        }
        bit_window >>= 1;
        bit_window_index -= 1;
    }
    buffer[buf_index] = '\0';
    return buffer;
}

char* get_non_binary_string(int integer, int base, char* const buffer, bool use_upper_case)
{
    int buff_len = 0;
    int temp_buff_len = 0;
    int dividend = integer;
    char temp_buffer[32];
    int alpha_base = use_upper_case ? 65 : 97;
    if (integer < 0)
    {
        dividend *= -1;
        buffer[0] = '-';
        buff_len += 1;
    }
    int remainder = 0;
    while (dividend > 0)
    {
        remainder = dividend % base;
        dividend /= base;
        if (remainder >= 10)
        {
            temp_buffer[temp_buff_len] = (remainder - 10) + alpha_base;
        }
        else
        {
            temp_buffer[temp_buff_len] = remainder + 48;
        }
        temp_buff_len += 1;
    }
    for(int c = temp_buff_len -1; c >= 0; c--, buff_len++)
    {
        buffer[buff_len] = temp_buffer[c];
    }
    buffer[buff_len] = '\0';
    return buffer;
}

char* itoa(int integer, int base, char* const buffer, bool use_upper_case)
{
    if(base == 2)
    {
        return get_binary_string(integer, buffer);
    }
    else
    {
        return get_non_binary_string(integer, base, buffer, use_upper_case);
    }
}

int chtoi(char c)
{
    if(c >= 48 && c <= 57)
    {
        return c - 48;
    }
    else if(c >= 65 && c <= 70)
    {
        return c - 65 + 10;
    }
    else if(c >= 97 && c <= 102)
    {
        return c - 97 + 10;
    }
    else
    {
        return -1;
    }
}

char* uitoa(unsigned int integer, int base, char* const buffer, bool use_upper_case)
{
    int buff_len = 0;
    int temp_buff_len = 0;
    unsigned int dividend = integer;
    char temp_buffer[32];
    int alpha_base = use_upper_case ? 65 : 97;
    unsigned int remainder = 0;
    while (dividend > 0)
    {
        remainder = dividend % base;
        dividend /= base;
        if (remainder >= 10)
        {
            temp_buffer[temp_buff_len] = (remainder - 10) + alpha_base;
        }
        else
        {
            temp_buffer[temp_buff_len] = remainder + 48;
        }
        temp_buff_len += 1;
    }
    for(int c = temp_buff_len -1; c >= 0; c--, buff_len++)
    {
        buffer[buff_len] = temp_buffer[c];
    }
    buffer[buff_len] = '\0';
    return buffer;
}

int putchar(int ch) {
	*UART0_ADDR = (unsigned int)ch;
	return ch;
}

int puts(const char* str) {
	int i = 0;
	for (; *str != '\0'; str++, i++) {
		*UART0_ADDR = (unsigned int)(*str);
	}
	return i;
}

int strlen(const char* const str)
{
    int count = 0;
    while(str[count] != '\0')
    {
        count += 1;
    }
    return count;
}

typedef struct pf_flags_t
{
    bool left_justify;
    bool prepend_plus;
    bool prepend_space;
    bool prepend_zero_for_padding;
    bool use_alternate_form;
} pf_flags_t;

typedef struct pf_params_t
{
    pf_flags_t flags;
    int width;
    int precision;
    char length;
} pf_params_t;



bool is_specifier_field(char c)
{
    return c == 'c' || c == 'd' || c == 'i' || c == 'e' \
           || c == 'E' || c == 'f' || c == 'g' || c == 'G' \
           || c == 'o' || c == 'S' || c == 'U' || c == 'x' \
           || c == 'X' || c == 'p' || c == 'n' || c == '%' || c == 'b';
}

bool is_flag_field(char c)
{
    return c == '-' || c == '+' || c == ' ' || c == '0' || c == '#';
}

bool is_length_field(char c)
{
    return c == 'h' || c == 'l' || c == 'L';
}

pf_flags_t get_flags_from_format(const char* const fmt, int* const fmt_index)
{
    pf_flags_t flags = {
        .left_justify = false,
        .prepend_plus = false,
        .prepend_space = false,
        .prepend_zero_for_padding = false,
        .use_alternate_form = false
        };
    char ch;
    while((ch = fmt[*fmt_index]) != '\0')
    {
        if(is_flag_field(ch))
        {
            if(ch == '-')
            {
                flags.left_justify = true;
            }
            else if(ch == '+')
            {
                flags.prepend_plus = true;
            }
            else if(ch == ' ')
            {
                flags.prepend_space = true;
            }
            else if(ch == '0')
            {
                flags.prepend_zero_for_padding = true;
            }
            else if(ch == '#')
            {
                flags.use_alternate_form = true;
            }
            else
            {
                break;
            }
            *fmt_index += 1;
        }
        else
        {
            break;
        }
    }
    return flags;
}

int get_number_from_format(const char* const fmt, int* const fmt_index)
{
    int number = 1;
    int temp_number = 0;
    int digit_index = 0;
    char ch;
    while((ch = fmt[*fmt_index]) != '\0')
    {
        if(is_number_char(ch))
        {
            temp_number = chtoi(ch);
            number = digit_index == 0 ? temp_number : number * 10 + temp_number;
            digit_index += 1;
            *fmt_index += 1;
        }
        else
        {
            break;
        }
    }
    return number;
}

int get_width_from_format(const char* const fmt, int* const fmt_index, va_list* const args)
{
    int width = -1;
    char ch = fmt[*fmt_index];
    if(ch == '*')
    {
        width = va_arg(*args, int);
        *fmt_index += 1;
    }
    else if(is_number_char(ch))
    {
        width = get_number_from_format(fmt, fmt_index);
    }
    return width;
}

int get_precision_from_format(const char* const fmt, int* const fmt_index, va_list* const args)
{
    int precision = -1;
    char ch = fmt[*fmt_index];
    if(ch == '.')
    {
        *fmt_index += 1;
        ch = fmt[*fmt_index];
        if(ch == '*')
        {
            precision = va_arg(*args, int);
            *fmt_index += 1;
        }
        else if(is_number_char(ch))
        {
            precision = get_number_from_format(fmt, fmt_index);
        }
    }
    return precision;
}

char get_length_from_format(const char* const fmt, int* const fmt_index)
{
    char length = '\0';
    if(is_length_field(fmt[*fmt_index]))
    {
        length = fmt[*fmt_index];
        *fmt_index += 1;
    }
    return length;
}

int pad_with_char(char c, int count)
{
    int write_count = 0;
    for(char x = 0; x < count; x++)
    {
        putchar(c);
        write_count++;
    }
    return write_count;
}

int print_char(char c, const pf_params_t* const params)
{
    int write_count = 0;
    int pad_diff = params->width > 0 ? params->width - 1 : 0;
    pf_flags_t flags = params->flags;
    if(flags.left_justify)
    {
        if(flags.prepend_zero_for_padding)
        {
            write_count += pad_with_char('0', pad_diff);
        }
        else
        {
            write_count += pad_with_char(' ', pad_diff);
        }
    }
    else
    {
        if(flags.prepend_zero_for_padding)
        {
            write_count += pad_with_char('0', pad_diff);
        }
        else
        {
            write_count += pad_with_char(' ', pad_diff);
        }
        putchar(c);
        write_count++;
    }
    return write_count;
}

int print_int(long long number, unsigned int base, const pf_params_t* const params, bool upper_case)
{
    char buf[32];
    char prefix_chars[3] = {'\0', '\0', '\0'};
    int write_count = 0;
    int prefix_count = 0;
    bool is_negative = false;
    itoa(number, base, (char*)&buf, upper_case);
    int str_len = strlen((char*)&buf);
    pf_flags_t flags = params->flags;
    int prec_diff = params->precision > 0 ? params->precision - str_len : 0;
    char signed_char;
    if(number < 0 && base == 10)
    {
        signed_char = '-';
        prec_diff = prec_diff >= 1 ? prec_diff + 1 : 0;
        is_negative = true;
    }
    else if(flags.prepend_plus && base == 10)
    {
        signed_char = '+';
    }
    else if(flags.prepend_space)
    {
        signed_char = ' ';
    }
    else
    {
        signed_char = '\0';
    }
    int p_index = 0;
    if(signed_char != '\0')
    {
        prefix_count += 1;
        prefix_chars[p_index++] = signed_char;
    }
    if(flags.use_alternate_form)
    {
        if(base == 8)
        {
            prefix_count += 1;
            prefix_chars[p_index++] = '0';
        }
        else if(base == 16)
        {
            prefix_count += 2;
            prefix_chars[p_index++] = '0';
            prefix_chars[p_index++] = upper_case ? 'X' : 'x';
        }
    }
    int potential_write_count = prefix_count + str_len;
    int width_diff = params->width > 0 ? params->width - potential_write_count : 0;
    if(!flags.left_justify)
    {
        if(flags.prepend_zero_for_padding)
        {
            write_count += pad_with_char('0', width_diff);
        }
        else
        {
            write_count += pad_with_char(' ', width_diff);
        }
    }
    char prefix;
    int index = 0;
    while((prefix = prefix_chars[index]) != '\0')
    {
        putchar(prefix);
        write_count += 1;
        index += 1;
    }
    write_count += pad_with_char('0', prec_diff);
    int start_index = is_negative ? 1 : 0;
    for(int i = start_index; i < str_len; i++)
    {
        putchar(buf[i]);
        write_count += 1;
    }
    if(flags.left_justify)
    {
        if(flags.prepend_zero_for_padding)
        {
            write_count += pad_with_char('0', width_diff);
        }
        else
        {
            write_count += pad_with_char(' ', width_diff);
        }
    }
    return write_count;
}

int print_uint(unsigned int number, unsigned int base, const pf_params_t* const params, bool upper_case)
{
    char buf[32];
    char prefix_chars[3] = {'\0', '\0', '\0'};
    int write_count = 0;
    int prefix_count = 0;
    bool is_negative = false;
    uitoa(number, base, (char*)&buf, upper_case);
    int str_len = strlen((char*)&buf);
    pf_flags_t flags = params->flags;
    int prec_diff = params->precision > 0 ? params->precision - str_len : 0;
    char signed_char;
    if(flags.prepend_space)
    {
        signed_char = ' ';
    }
    else
    {
        signed_char = '\0';
    }
    int p_index = 0;
    if(signed_char != '\0')
    {
        prefix_count += 1;
        prefix_chars[p_index++] = signed_char;
    }
    if(flags.use_alternate_form)
    {
        if(base == 8)
        {
            prefix_count += 1;
            prefix_chars[p_index++] = '0';
        }
        else if(base == 16)
        {
            prefix_count += 2;
            prefix_chars[p_index++] = '0';
            prefix_chars[p_index++] = upper_case ? 'X' : 'x';
        }
    }
    int potential_write_count = prefix_count + str_len;
    int width_diff = params->width > 0 ? params->width - potential_write_count : 0;
    if(!flags.left_justify)
    {
        if(flags.prepend_zero_for_padding)
        {
            write_count += pad_with_char('0', width_diff);
        }
        else
        {
            write_count += pad_with_char(' ', width_diff);
        }
    }
    char prefix;
    int index = 0;
    while((prefix = prefix_chars[index]) != '\0')
    {
        putchar(prefix);
        write_count += 1;
        index += 1;
    }
    write_count += pad_with_char('0', prec_diff);
    int start_index = is_negative ? 1 : 0;
    for(int i = start_index; i < str_len; i++)
    {
        putchar(buf[i]);
        write_count += 1;
    }
    if(flags.left_justify)
    {
        if(flags.prepend_zero_for_padding)
        {
            write_count += pad_with_char('0', width_diff);
        }
        else
        {
            write_count += pad_with_char(' ', width_diff);
        }
    }
    return write_count;
}


int print_binary(int number, const pf_params_t* const params)
{
    int write_count = 0;
    char bit_buff[33];
    itoa(number, 2, (char*)&bit_buff, false);
    int str_len = strlen((char*)&bit_buff);
    pf_flags_t flags = params->flags;
    int prec_diff = params->precision > 0 ? params->precision - str_len : 0;
    int potential_write_count = str_len + prec_diff;
    int width_diff = params->width > 0 ? params->width - potential_write_count : 0;
    if(!flags.left_justify)
    {
        if(flags.prepend_zero_for_padding)
        {
            write_count += pad_with_char('0', width_diff);
        }
        else
        {
            write_count += pad_with_char(' ', width_diff);
        }
    }
    write_count += pad_with_char('0', prec_diff);
    for(int i = 0; i < str_len; i++)
    {
        putchar(bit_buff[i]);
        write_count += 1;
    }
    if(flags.left_justify)
    {
        if(flags.prepend_zero_for_padding)
        {
            write_count += pad_with_char('0', width_diff);
        }
        else
        {
            write_count += pad_with_char(' ', width_diff);
        }
    }
    return write_count;
}


int print_string(const char* const str, const pf_params_t* const params)
{
    int write_count = 0;
    int str_len = strlen(str);
    int chars_to_write = params->precision > 0 && str_len > params-> precision ? params->precision : str_len;
    int width_diff = params->width > 0 ? params->width - chars_to_write : 0;
    pf_flags_t flags = params->flags;
    if(!flags.left_justify)
    {
        write_count += pad_with_char(' ', width_diff);
    }
    char ch;
    int str_index = 0;
    while((ch = str[str_index]) != '\0')
    {
        putchar(ch);
        write_count += 1;
        str_index += 1;
    }
    if(flags.left_justify)
    {
        write_count += pad_with_char(' ', width_diff);
    }
    return write_count;
}

int print_specifier_value(const char* const fmt, int* const fmt_index, const pf_params_t* const params, va_list* const args)
{
    int write_count = 0;
    char ch = fmt[*fmt_index];
    if(ch != '\0')
    {
        if(ch == 'c' || ch == '%')
        {
            char c = va_arg(*args, int);
            write_count += print_char(c, params);
            *fmt_index += 1;
        }
        else if(ch == 'd' || ch == 'i' || ch == 'u')
        {
            int number = va_arg(*args, int);
            write_count += print_int(number, 10, params, false);
            *fmt_index += 1;
        }
        else if(ch == 'b')
        {
            int number = va_arg(*args, int);
            write_count += print_binary(number, params);
            *fmt_index += 1;
        }
        else if(ch == 'o')
        {
            int number = va_arg(*args, int);
            write_count += print_int(number, 8, params, false);
            *fmt_index += 1;
        }
        else if(ch == 'x')
        {
            unsigned int number = va_arg(*args, unsigned int);
            write_count += print_uint(number, 16, params, false);
            *fmt_index += 1;
        }
        else if(ch == 'X')
        {
            unsigned int number = va_arg(*args, unsigned int);
            write_count += print_uint(number, 16, params, true);
            *fmt_index += 1;
        }
        else if(ch == 'p')
        {
            pf_params_t force_params = {
                .flags = params->flags,
                .precision = 0,
                .width = 0,
                .length = '\0'
            };
            force_params.flags.use_alternate_form = true;
            unsigned int number = va_arg(*args, unsigned int);
            write_count += print_uint(number, 16, (pf_params_t*)&force_params, false);
            *fmt_index += 1;
        }
        else if(ch == 's')
        {
            const char* const str = va_arg(*args, const char* const);
            write_count += print_string(str, params);
            *fmt_index += 1;
        }

    }
    return write_count;
}


int process_format_string(const char* const fmt, int* const fmt_index, va_list* const args)
{
    pf_flags_t flags = get_flags_from_format(fmt, fmt_index);
    int width = get_width_from_format(fmt, fmt_index, args);
    int precision = get_precision_from_format(fmt, fmt_index, args);
    char length = get_length_from_format(fmt, fmt_index);
    pf_params_t params;
    params.flags = flags;
    params.length = length;
    params.precision = precision;
    params.width = width;
    int write_count = print_specifier_value(fmt, fmt_index, (pf_params_t*)&params, args);
    return write_count;
}


int printf(const char* const fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int write_count = 0;
    int fmt_index = 0;
    char ch;
    while((ch = fmt[fmt_index]) != '\0')
    {
        if(ch == '%')
        {
            fmt_index += 1;
            write_count += process_format_string(fmt, (int*)&fmt_index, (va_list*)&args);

        }
        else
        {
            putchar(ch);
            fmt_index += 1;
            write_count += 1;
        }
    }
    va_end(args);
    return write_count;
}
