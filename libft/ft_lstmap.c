/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:53:53 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/16 14:25:14 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;
	t_list	*temp;
	t_list	*tempd;

	if (lst == NULL)
		return (NULL);
	dest = ft_lstnew(f(lst->content));
	tempd = dest;
	temp = lst->next;
	while (temp != NULL)
	{
		tempd->next = ft_lstnew(f(temp->content));
		if (tempd->content == NULL)
		{
			ft_lstclear(&dest, del);
			return (NULL);
		}
		temp = temp->next;
		tempd = tempd->next;
	}
	return (dest);
}
