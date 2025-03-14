/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection_handling.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenev <spenev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:17:13 by stfn              #+#    #+#             */
/*   Updated: 2024/12/09 11:37:21 by spenev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

/* 
 * Maps a token type to a corresponding redirection type. This function checks 
 * the token type and assigns the appropriate redirection type to the provided 
 * redirection type pointer. Returns 1 if successful, otherwise returns 0.
 */
int	map_token_to_redirection(t_token_type token_type,
	t_redirection_type *redir_type)
{
	if (!redir_type)
		return (0);
	if (token_type == TOKEN_REDIRECT_IN)
	{
		*redir_type = REDIRECT_INPUT;
		return (1);
	}
	else if (token_type == TOKEN_REDIRECT_OUT)
	{
		*redir_type = REDIRECT_OUTPUT;
		return (1);
	}
	else if (token_type == TOKEN_APPEND)
	{
		*redir_type = REDIRECT_APPEND;
		return (1);
	}
	else if (token_type == TOKEN_HEREDOC)
	{
		*redir_type = HEREDOC;
		return (1);
	}
	else
		return (0);
}

/* 
 * Appends a new redirection to the end of the linked list of redirections. 
 * If the head of the list is NULL, the new redirection becomes the head. 
 * Otherwise, the function traverses to the end of the list and links the 
 * new redirection to the last node.
 */
void	append_redirection(t_redirection **head, t_redirection *new_redir)
{
	t_redirection	*last;

	if (!*head)
	{
		*head = new_redir;
	}
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

static void	handle_existing_redirections(t_command *command,
	t_redirection *new_redir)
{
	t_redirection	*current;
	t_redirection	*previous;

	current = command->redirections;
	previous = NULL;
	while (current)
	{
		if (current->type == new_redir->type)
		{
			if (previous)
				previous->next = new_redir;
			else
				command->redirections = new_redir;
			new_redir->next = current->next;
			free(current->filename);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
	previous->next = new_redir;
	new_redir->next = NULL;
}

void	add_redirection_to_command(t_command *command, t_redirection *new_redir)
{
	if (!command->redirections)
	{
		command->redirections = new_redir;
		return ;
	}
	handle_existing_redirections(command, new_redir);
}

t_redirection	*parse_redirection(t_parser *parser)
{
	t_redirection	*redir;

	if (!parser->current_token
		|| !is_redirection_token(parser->current_token->type))
		return (NULL);
	redir = allocate_redirection();
	if (!redir)
		return (NULL);
	map_token_to_redirection(parser->current_token->type, &redir->type);
	parser_advance(parser);
	if (redir->type == HEREDOC)
	{
		if (!handle_heredoc(parser, redir))
			return (NULL);
	}
	else
	{
		if (!handle_redirection_filename(parser, redir))
			return (NULL);
	}
	return (redir);
}
