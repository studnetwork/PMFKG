import { Injectable } from '@angular/core';
import { ActivatedRouteSnapshot, CanActivate, RouterStateSnapshot, UrlTree } from '@angular/router';
import { JwtHelperService } from '@auth0/angular-jwt';
import { Observable } from 'rxjs';
import { JwtService } from '../srv/jwt.service';

@Injectable({
  providedIn: 'root'
})
export class LoggedOutGuard implements CanActivate {
  
  constructor(
    private jwtService: JwtService
  ) { }

  canActivate(): boolean {
    return this.jwtService.isJwtExpired();
  }

  // canActivate(
  //   route: ActivatedRouteSnapshot,
  //   state: RouterStateSnapshot
  // ): boolean {
  //   return true
  // }
  
}
