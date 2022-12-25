import { HttpErrorResponse } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Router } from '@angular/router';
import { AuthService } from '../auth/auth.service';

/**
 * Kreirano sa: `ng g s core/services/http-error-handler`
 * 
 * **Napomena**: za ovo je ispravnije koristiti interceptor, a ne servis
 */
@Injectable({
  providedIn: 'root'
})
export class HttpErrorHandlerService {

  constructor(
    private authService: AuthService,
    private router: Router) { }

  handle(returnedError: any): string {
    let errorMessage = "";

    if (returnedError instanceof Error)
      console.log(`${returnedError as Error}`);

    if (returnedError instanceof HttpErrorResponse)
      console.log(`Error Status ${returnedError.status}: ${returnedError.message}`);

    switch (returnedError.status) {
      case 400:
        errorMessage = returnedError.error.message; 
        break;

      case 401:
        this.authService.deleteJwt();
        this.router.navigate(["/login"]);
        break;
        
      case 403:
        this.authService.deleteJwt();
        this.router.navigate(["/login"]);
        break;
    
      default:
        errorMessage = "Nesto nije u redu";
        break;
    }

    return errorMessage;
  }
}
