import { Book } from "./book.model";

/**
 * Kreirano sa: `ng g interface core/models/author --type=model`
 */
export interface Author {
	_id: string,
    name: string;
	surname: string;
	dateOfBirth: number;
	books?: Book[];
}
