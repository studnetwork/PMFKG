import { Author } from "./author.model";

/**
 * Kreirano sa: `ng g interface core/models/book --type=model`
 */
export interface Book {
	_id: string,
    title: string;
	author?: Author;
	yearOfPublication: number;
}
